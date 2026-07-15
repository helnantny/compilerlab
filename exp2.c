#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "while",
    "for", "return", "void", "break", "continue", "switch",
    "case", "default", "do", "struct", "long", "short", "const"
};

int isKeyword(char str[]) {
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    FILE *fp;
    char ch, buffer[100];
    int i;

    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Cannot open input file.\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF) {

        // Ignore spaces, tabs, newlines
        if (isspace(ch))
            continue;

        // Ignore comments
        if (ch == '/') {
            char next = fgetc(fp);

            if (next == '/') {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            }
            else if (next == '*') {
                char prev = 0;
                while ((ch = fgetc(fp)) != EOF) {
                    if (prev == '*' && ch == '/')
                        break;
                    prev = ch;
                }
                continue;
            }
            else {
                printf("/\t\tOperator\n");
                ungetc(next, fp);
                continue;
            }
        }

        // Identifier or Keyword
        if (isalpha(ch) || ch == '_') {
            i = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                  (isalnum(ch) || ch == '_'))
                buffer[i++] = ch;

            buffer[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            if (isKeyword(buffer))
                printf("%-12s Keyword\n", buffer);
            else
                printf("%-12s Identifier\n", buffer);
        }

        // Integer or Float
        else if (isdigit(ch)) {
            i = 0;
            int dot = 0;
            buffer[i++] = ch;

            while ((ch = fgetc(fp)) != EOF &&
                  (isdigit(ch) || ch == '.')) {
                if (ch == '.') {
                    if (dot)
                        break;
                    dot = 1;
                }
                buffer[i++] = ch;
            }

            buffer[i] = '\0';

            if (ch != EOF)
                ungetc(ch, fp);

            printf("%-12s Number\n", buffer);
        }

        // Operators
        else if (strchr("+-*=<>!%", ch)) {
            printf("%-12c Operator\n", ch);
        }

        // Delimiters
        else if (strchr("(){}[];,", ch)) {
            printf("%-12c Delimiter\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
