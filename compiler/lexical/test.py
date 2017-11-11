# tokenizer for a simple expression evaluator for
# numbers and +,-,*,/
# ------------------------------------------------------------
import lex

# List of token names.   This is always required
tokens = (
    'NUMBER',
    'OP',
    'LPAREN',
    'RPAREN',
    'VARIABLE',
    'TYPE',
    'WHITE_SPACE'
)

# Regular expression rules for simple tokens

t_LPAREN  = r'\('
t_RPAREN  = r'\)'

# A regular expression rule with some action code
def t_OP(t):
    r'\+|-|\*|/'
    return t
def t_WHITE_SPACE(t):
    r' \r|\n|\r\n|\t'
    return t
def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t
def t_VARIABLE(t):
    r'[a-zA-Z_][0-9a-zA-Z_]*'
    t.value = str(t.value)
    return t

# Define a rule so we can track line numbers
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# A string containing ignored characters (spaces and tabs)
t_ignore  = ' \t'

# Error handling rule
def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()

# Test it out
data = '''
3 + 4 * 10
  + -20 *2
  aaaVb
  asdfDe
  _dsf
  1df
'''

# Give the lexer some input
lexer.input(data)
lexer.writetab(lextab='lextab')

# Tokenize
while True:
    tok = lexer.token()
    if not tok:
        break      # No more input
    print(tok)