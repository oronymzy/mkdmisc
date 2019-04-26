# Markdown miscellany
This is a collection of Markdown programs that perform miscellaneous tasks.

Currently there is only one program (change plain URLs to Markdown automatic links), but more are planned.

## change plain URLs to Markdown automatic links

| Note:
|:-
| Two consecutive spaces (`  `) are represented by two dots (`⋅⋅`).

This program turns any plain URLs in a text file into Markdown [automatic links](http://www.tips.mostserio.us/Mdwnref/#alink). Automatic links are created by placing a less-than sign (`<`) on the left and a greater-than sign (`>`) on the right. Additionally, if the plain URL is not followed by a line containing only a newline, the greater-than sign (`>`) is followed by two spaces (`⋅⋅`) in order to produce [a Markdown hard line break](http://www.tips.mostserio.us/Mdwnref/#hlbreaktwospace).

It is written in [C++](https://en.wikipedia.org/wiki/C%2B%2B).
