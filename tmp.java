public class Solution {
    /**
     * @param generator: Generating set of rules.
     * @param startSymbol: Start symbol.
     * @param symbolString: Symbol string.
     * @return: Return true if the symbol string can be generated, otherwise return false.
     */
    public boolean canBeGenerated(String[] generator, char startSymbol, String symbolString) {
        // Write your code here.
        Map<Character, List<String> >map = new HashMap<Character, List<String> >();
        for(int i = 0;i < generator.length; i++) {
            Character start = generator[i].charAt(0);
            String tostring = generator[i].substring(5);
            if(map.get(start) == null) {
                map.put(start, new ArrayList<String>());
            }
            map.get(start).add(tostring);
        }
        String x = String.valueOf(startSymbol);
        System.out.println(symbolString);
        return dfs(map, x, symbolString);
    }
    
    public boolean dfs(Map<Character, List<String> >map, String x, String symbolString) {
        if(x.length() > symbolString.length()) {
            return false;
        }
        if(x.equals(symbolString)) {
            return true;
        }
        for(int i = 0; i < x.length(); i++) {
            if(x.charAt(i) >= 'A' && x.charAt(i) <= 'Z') {
                for(String j : map.get(x.charAt(i))) {
                    String tmp = new String();
                    if(i > 0) {
                        tmp = x.substring(0, i);
                    }
                    tmp += j;
                    if(i + 1 < x.length()) {
                        tmp = tmp + x.substring(i + 1);
                    }
                    boolean ans = dfs(map, tmp, symbolString);
                    if(ans == true) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}
