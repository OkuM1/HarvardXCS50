import os
import cs50

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, jsonify, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    portfolio = db.execute("SELECT user_id, symbol, shares FROM portfolio WHERE user_id = ? GROUP BY symbol", user_id)
    cash_dict = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash_balance = cash_dict[0]["cash"]

    current_price = {}
    total = {}

    for stock in portfolio:
        total[stock["symbol"]] = lookup(stock["symbol"])["price"] * int(stock["shares"])
        current_price[stock["symbol"]] = lookup(stock["symbol"])["price"]

    return render_template("index.html", portfolio=portfolio, cash_balance=cash_balance, total=total, current_price=current_price)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Apology if user does not provide symbol or shares for buy
        if not symbol:
            return apology("please write symbol",400)

        if not shares.isdigit():
            return apology("you cannot purchase partial shares.")

        if not shares:
            return apology("please specifiy share amount", 400)

        shares = int(request.form.get("shares"))

        # Initiate better value types
        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Does not exist.", 400)

        total_cost = stock["price"] * shares
        user_id = session["user_id"]

        # Query current user balance
        current_balance_dict = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_balance = current_balance_dict[0]["cash"]

        updated_balance = current_balance - total_cost

        # Update db
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_balance, user_id)

        date = datetime.datetime.now()
        # record in history
        db.execute("INSERT INTO history (user_id, symbol, shares, method, price, date, total) VALUES (?, ?, ?, ?, ?, ?, ?)",
                    user_id, stock["symbol"], shares, "BUY", stock["price"], date, total_cost)

        # update portfolio
        check = db.execute("SELECT symbol FROM portfolio WHERE symbol= :symbol AND user_id= :user_id",
                            symbol=request.form.get("symbol"), user_id=session["user_id"])

        if len(check) != 1:

            update = db.execute("INSERT INTO portfolio (user_id, symbol, shares) VALUES (:user_id,:symbol,:shares)",
                                 user_id=session["user_id"], symbol=request.form.get("symbol"), shares=request.form.get("shares"))
        else:

            quant = db.execute("SELECT shares FROM portfolio WHERE user_id= :user_id AND symbol= :symbol ",
                                user_id=session["user_id"], symbol=request.form.get("symbol"))
            update = db.execute("UPDATE portfolio SET shares= :q WHERE symbol= :symbol AND user_id= :user_id",
                                 q=int(quant[0]["shares"])+int(request.form.get("shares")), symbol=request.form.get("symbol"),user_id=session["user_id"])

        flash("Bought shares")

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]

    history_data = db.execute("SELECT * FROM history WHERE user_id = ? ORDER BY date DESC", user_id)

    return render_template("history.html", history_data=history_data)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add Cash to Balance"""

    if request.method == "GET":
        return render_template("add_cash.html")

    if request.method == "POST":

        # Post amount of usd entered in add_cash
        cash_add = int(request.form.get("cash_add"))
        user_id = session["user_id"]

        if not cash_add:
            return apology("Must enter amount", 400)

        # Query current user balance
        current_balance_dict = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_balance = current_balance_dict[0]["cash"]

        updated_balance = current_balance + cash_add

        # Update db
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_balance, user_id)

        return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":

        symbol = request.form.get("symbol")

        if not symbol:
            return apology("pls enter symbol", 400)

        result = lookup(request.form.get("symbol"))

        if result == None:
            return apology("invalid stock symbol", 400)
        return render_template("quoted.html", result=result)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":

        return render_template("register.html")

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure password matches confirmation
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password does not match with confirmation", 400)

        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))

        # insert username and hashed password into database
        try:
            user = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        except:
            return apology("username taken", 400)

        session["user_id"] = user

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":

        # Query all stocks in portfolio
        my_stocks = db.execute("SELECT symbol FROM history WHERE user_id = :id GROUP BY symbol",
                               id=session["user_id"])

        return render_template("sell.html", my_stocks=my_stocks)

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Apology if user does not provide symbol or shares for buy
        if not symbol:
            return apology("please write symbol", 400)

        if not shares.isdigit():
            return apology("you cannot sell partial shares", 400)

        if not shares:
            return apology("please specifiy share amount", 400)

        # Initiate better value types
        shares = int(request.form.get("shares"))
        stock = lookup(symbol.upper())
        total_cost = stock["price"] * shares
        user_id = session["user_id"]

        # Query current user balance
        current_balance_dict = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_balance = current_balance_dict[0]["cash"]

        # Check if shares available to be sold
        total_shares_dict = db.execute(
            "SELECT shares FROM history WHERE user_id = ? AND symbol = ? GROUP BY symbol HAVING shares > 0", user_id, symbol)
        total_shares = total_shares_dict[0]["shares"]

        if shares > total_shares:
            return apology("Do not own enough shares", 400)

        updated_balance = current_balance + total_cost

        # Update db
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updated_balance, user_id)

        date = datetime.datetime.now()

        db.execute("INSERT INTO history (user_id, symbol, shares, method, price, date, total) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], -1 * shares, "SELL", stock["price"], date, total_cost)

        # update portfolio
        quantity = db.execute("SELECT shares FROM portfolio WHERE user_id= :user_id AND symbol= :symbol",
                              user_id=session["user_id"], symbol=request.form.get("symbol"))

        update = db.execute("UPDATE portfolio SET shares= :q WHERE user_id=:user_id AND symbol= :symbol",
                            q=int(quantity[0]["shares"])-int(request.form.get("shares")), user_id=session["user_id"], symbol=request.form.get("symbol"))

        flash("Sold shares")

        return redirect("/")

