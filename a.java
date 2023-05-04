    private static final char OPEN_BRACE_CHAR = '[';
    private static final char CLOSE_BRACE_CHAR = ']';    
    private static final String OPEN_BRACE_STR = "[";
    private static final String CLOSE_BRACE_STR = "]";
    
    public String decodeString(String s) {
        Stack<Integer> numStack = new Stack<>();
        Stack<String> varStack = new Stack<>();
        
        
        for (int i = 0; i < s.length(); i++) {
            
            char currentChar = s.charAt(i);
            if (Character.isDigit(currentChar)) {
                int numberStartIndex = i;
                // Extract the full number and push it into the numstack
                while (i + 1 < s.length() && Character.isDigit(s.charAt(i + 1))) {
                    i++;
                }
                int number = Integer.parseInt(s.substring(numberStartIndex, i + 1));
                numStack.push(number);  
            } else if (currentChar == OPEN_BRACE_CHAR) {
                // Insert the open brace in to the stack
                varStack.push(String.valueOf(currentChar));
            } else if (currentChar == CLOSE_BRACE_CHAR) { 
                // Keep popping till we see an OPEN_BRACE and append all these strings together
                // Since we are popping out of the stack, should preserve the order
                // So we should insert at 0 as we take elements out of the stack
                StringBuilder tmpStringBuilder1 = new StringBuilder();
                while (!varStack.peek().equals(OPEN_BRACE_STR)) {
                    tmpStringBuilder1.insert(0, varStack.pop());
                }
                String tmpString1 = tmpStringBuilder1.toString();
                // Pop the open brace
                varStack.pop();
                
                StringBuilder tmpStringBuilder2 = new StringBuilder();
                int count = numStack.pop();
                for (int j = 0; j < count; j++) {
                    tmpStringBuilder2.append(tmpString1);
                }

                // Push the result to TopOfStack
                varStack.push(tmpStringBuilder2.toString());
                
            } else {
                varStack.push(String.valueOf(currentChar));
            }
        }
        
        StringBuilder decodeResultBuilder = new StringBuilder();
        while (!varStack.isEmpty()) {
            decodeResultBuilder.insert(0, varStack.pop());
        }
        return decodeResultBuilder.toString();
    }