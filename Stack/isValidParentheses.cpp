bool isValidParentheses (string s){
    std::stack<char> chars;
    for (char ch : s) {
        // first condition is to overcome cases like ")(("
        if (chars.size() == 0) {
            chars.push(ch);  
        } else if (ch == ']') {
            if (chars.top() != '[') return false;
            chars.pop();
        } else if (ch ==')') {
            if (chars.top() != '(') return false;
            chars.pop();
        } else if (ch == '}') {
            if (chars.top() != '{') return false;
            chars.pop();
        } else if (ch == '[' || ch == '(' || ch == '{') {
            chars.push(ch);
        }
    }
    return chars.size() == 0;
}
