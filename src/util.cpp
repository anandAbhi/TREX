/**
 * Name: Abhinav Anand
 * Roll Number: 2018201037
**/


#include "util.h"

/**
 * converts timestamp to localtime
 * @param timestamp
 * @return string representation of time
 */
std::string timestamp_to_localtime(time_t timestamp) {
    struct tm lt;
    localtime_r(&timestamp, &lt);
    char timbuf[80];

    // source https://stackoverflow.com/a/13542409/5463404
    strftime(timbuf, sizeof(timbuf), "%d.%m.%Y %H:%M", &lt);
    return timbuf;
}

std::string pwd() {
    char *cwd = get_current_dir_name();
    return cwd;
}

bool dir_exists(const std::string &path) {
    DIR *dirptr;

    // we need to use c_str() bcoz opendir accepts on char * and converting
    // our name to char * copies some invalid characters into it.
    if ((dirptr = opendir(path.c_str())) == nullptr) {
        return false;
    }

    closedir(dirptr);
    return true;
}

std::string get_proper_path(const std::string &path, const std::string &HOME_PATH) {
    if (path == "/" || path == "~")
        // goto APP_ROOT aka HOME_PATH
        return HOME_PATH;
    if (path[0] == '/')
        // APP ROOT relative path
        return HOME_PATH + "/" + path.substr(1);  // substr(1) == from index 1 till the end
    if (path[0] == '~' and path[1] == '/')
        // APP ROOT relative path in different notation
        return HOME_PATH + "/" + path.substr(2);  // substr(2) means skip ~/ in ~/foobar

    // currrent directory relative path
    return path;
}

std::vector<std::string> escaped_tokenizer(std::string command) {
    std::vector<std::string> tokens;
    std::string token;
    bool escaped = false;
    char escape_char = '\'';

    for (char c: command) {
        // build the token until we encounter a space
        if (c == ' ' and !escaped) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if ((c == '\'' || c == '\"') and !escaped) {
            escape_char = c;
            escaped = !escaped;
        } else if (c == escape_char) {
            escaped = !escaped;
        } else {
            token += c;
        }
    }
    tokens.push_back(token);    // push last token

    return tokens;
}
