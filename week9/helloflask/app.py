from flask import Flask, render_template, request

app = Flask(__name__)

# request.get is for "GET"

# request.form is for "POST"

COLORS = [
    "red",
    "blue"]


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html")
    else:
        print("Form submitted!")
        color = request.form.get("color")
        if color not in COLORS:
            return render_template("error.html", message="Missing name")
        return render_template("color.html", color=color)