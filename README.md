Word-Ladder
===========

Displays if exists all word ladders between two words

**=== Context ===**  
A word ladder is a connection from one word to another formed by changing one letter at a time with the constraint that at each step the sequence of letters still forms a valid real word. For example, here is a word ladder connecting “code” to “data”.

    code -> cade -> cate -> date -> data

**=== Usage ===**  

    ./wl
    Enter start word (RETURN to quit): work
    Enter destination word: play
    Found ladder: work fork form foam flam flay play
    etc...

**=== Internals ===**  
- Uses a Breadth First Search.
