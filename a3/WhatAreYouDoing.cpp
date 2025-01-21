#include "WhatAreYouDoing.h"
#include "strlib.h"
#include <cctype>
#include "set.h"
#include "vector.h"
using namespace std;

//Vector<string> tokenize(const string& sentence);
Set<string> recursionEmphase(Vector<string>& tokens);
Set<string> recursionEmphase(const Vector<string>& tokens, Vector<string>& mytokens,int pos);

Set<string> allEmphasesOf(const string& sentence) {
    /* TODO: Delete this line and the next one, then implement this function. */
    Vector<string> tokens = tokenize(sentence);
    Vector<string> mytokens(tokens.size(),"aa");
    return recursionEmphase(tokens, mytokens, 0);
    //return recursionEmphase(tokens);
}
// solution one
Set<string> recursionEmphase(Vector<string>& tokens){
    Set<string> myset;
    if(tokens.isEmpty()){
        return myset += "";
    }else{
        string str = "",upstr = "";
        while(!tokens.isEmpty() && !isalpha(tokens.get(0)[0])){
            str += tokens.get(0);
            upstr = str;
            tokens.remove(0);
        }
        if(tokens.isEmpty()){
            myset += str;
        }else{
            upstr += toLowerCase(tokens.get(0));
            str += toUpperCase(tokens.get(0));
            tokens.remove(0);
        }
        for(string addstr : recursionEmphase(tokens)){
            myset += str + addstr;
            myset += upstr + addstr;
        }
        return myset;
    }
}
Set<string> recursionEmphase(const Vector<string>& tokens, Vector<string>& mytokens,int pos){
    Set<string> myset;
    if(pos == tokens.size()){
        string str = "";
        for(string elem : mytokens){
            str += elem;
        }
        myset += str;
        return myset;
    }
    if(!isalpha(tokens[pos][0])){
        mytokens[pos] = tokens[pos];
        myset += recursionEmphase(tokens, mytokens, pos + 1);
        return myset;
    }
    mytokens[pos] = toUpperCase(tokens[pos]);
    myset += recursionEmphase(tokens, mytokens, pos + 1);
    mytokens[pos] = toLowerCase(tokens[pos]);
    myset += recursionEmphase(tokens, mytokens, pos + 1);
    return myset;
}
// Vector<string> tokenize(const string& sentence){

//     Vector<string> tokens;
//     int wordstart = -1;
//     for(int i=0; i < sentence.length() - 1; i++){
//         if(isalpha(sentence[i])){
//             if(wordstart == -1){
//                 wordstart = i;
//             }
//         }else{
//             if(wordstart != -1){
//                 tokens.add(toLowerCase(sentence.substr(wordstart, i - wordstart)));
//             }
//             tokens.add(string(1,sentence[i]));

//         }
//     }
//     return tokens;
// }
/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}

PROVIDED_TEST("Stress Test: Recursion only branches on words (should take under a second)") {
    /* We're producing a string consisting of fifty copies of the * character. This tokenizes
     * into fifty separate stars. A star is the same whether or not you capitalize it - there
     * is no such thing as an "upper-case" or "lower-case" star. Therefore, your code should
     * not try to form two versions of the sentence, one with the star capitalized and one
     * without, because the two versions will end up being the same and the work to compute
     * both options will dramatically increase the runtime.
     *
     * For reference, if you do try branching the recursion and checking what happens both if
     * you capitalize the star and if you don't, you'll try exploring 2^50 different possible
     * capitalizations. That's 1,125,899,906,842,624 options, and even doing a billion of
     * these a second is going to take over two years to generate them all! And of course,
     * that's all wasted work, since there's only one way to capitalize this sentence, and
     * that's just to leave it as-is.
     *
     * If your code is hanging when this test is running, it likely means that your code is
     * trying to enumerate all of these options. See if you can edit your code so that, if
     * you're given a non-word token, you just leave it as-is and don't change anything.
     */
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}

PROVIDED_TEST("Stress test: Generates each option once (should take at most a few seconds)") {
    /* This sentence has 13 words in it. There are therefore 2^13 = 8192 possible emphases for
     * the words there, which is a big number but not so large that the computer can't handle
     * it if generates each emphasis exactly once.
     *
     * On the other hand, if your code tries to generate the same emphases multiple times,
     * this test may take a very, very long time to complete, and might even appear to freeze
     * up.
     *
     * If your code gets stuck in this test, trace through your code and confirm that you can't
     * produce the same emphasis multiple times. Check to make sure you aren't, for example,
     * looping over every token in the input sentence and deciding which one to capitalize
     * next. The recursion here follows more of an include/exclude type pattern (more like
     * subsets and combinations) than it does a "which is next?" type pattern (more like
     * permutations).
     */
    string yeats = "Turing and turning in a widening gyre / the falcon cannot hear the falconer.";
    EXPECT_EQUAL(allEmphasesOf(yeats).size(), 8192);
}
