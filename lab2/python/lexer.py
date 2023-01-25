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
