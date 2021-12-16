#include <stdio.h>
#include <string.h>

#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain("guess_num", LOCALE_DIR);
    textdomain("guess_num");

    printf(_("Guess a number from 1 to 100\n"));

    int answer_num = 0;
    int left = 1, right = 100;
    while (!answer_num) {
        int mid = left + (right - left) / 2;

        printf(_("Your number is greater than %d? yes/no "), mid);

        char *user_answer = NULL;
        size_t user_answer_len;
        getline(&user_answer, &user_answer_len, stdin);
        user_answer[strcspn(user_answer, "\n")] = 0;

        if (strcmp(user_answer, _("yes")) == 0) {
            left = mid + 1;
        } else {
            right = mid;
        }

        if (right <= left)
            answer_num = right;
    }

    printf(_("You guessed number %d\n"), answer_num);
}