from cs50 import get_string

def main():

    get_Input()


def get_Input():

    answer = get_string("Greeting: ")
    a = answer.strip().lower()

    if "hello" in a:
        print("$0")
    elif a.startswith("h"):
        print("$20")
    else:
        print("$100")

main()