import re
import sys

class Token:
    def __init__(self):
        self.tokenClass = ""
        self.original = ""

if len(sys.argv) < 2:
    print("Usage: python3 " + sys.argv[0] + " [source_file]")
    sys.exit(1)

tokens = []
    
for line in open(sys.argv[1],"r"):
    m = re.match("(\w+)\((\w+)\)",line)
    if m:
        token = Token()
        token.original = m.group(1)
        token.tokenClass = "FUNCTION"
        tokens.append(token)

        token = Token()
        token.original = m.group(2)
        token.tokenClass = "ARGUMENT"
        tokens.append(token)

print("Tokens found")
print("------------------")
for token in tokens:
    print(token.tokenClass + " - " + token.original)

statements = []

print("\n\nCreating Abstract Syntax Tree\n")

def argument(stmt, token):
    if token.tokenClass == "ARGUMENT":
        print("Found argument")
        stmt["statements"].append(token)
        return True
    else:
        print("Syntax error at token: " + token.original + "\n")
        return False

def accept(token, tokens):
    if token.tokenClass == "FUNCTION":
        print("Found function")
        stmt = {}
        stmt["type"] = "FunctionCall"
        stmt["statements"] = [token]
        statements.append(stmt)

        nextToken = tokens[0]
        tokens.pop(0)

        if argument(stmt,nextToken):
            if len(tokens) > 0:
                nextToken = tokens[0]
                tokens.pop(0)
                return accept(nextToken,tokens)
            else:
                return True
    print("Syntax error at token: " + token.original)
    return False

firstToken = tokens[0]
tokens.pop(0)

accepted = accept(firstToken,tokens)

if accepted:
    print("\n\nFinal Abstract Syntax Tree\n")
    for stmt in statements:
        print(stmt["type"])
        for sub in stmt["statements"]:
            print("    " + sub.tokenClass)
            print("        " + sub.original)
else:
    print("Failed to parse file: " + sys.argv[1])    
