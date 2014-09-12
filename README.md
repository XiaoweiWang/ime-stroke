#ime-stroke

###chinese ime - stroke

The "ime-stroke" is a simplified Chinese input method using strokes of the Chinese characters.

The main data structure applied in the search is improved ternary search tree, which is useful in prefix match search.

The search method requires 2 dictionaries:
* Chinese character dictionary with their stroke order and sorted by frequency.
* Chinese phrase dictionary sorted by frequency.

The raw character dictionary with stroke is *stroke.dict.yaml*, released under BSD license:
https://github.com/lotem/brise/blob/master/AUTHORS#L27.
The raw character and phrase frequency dictionary is *rawdict_utf16_65105_freq.txt*, which is part of Android Pinyin IME and licensed 
under the Apache Version 2.0, 2012.
http://android.googlesource.com/platform/packages/inputmethods/PinyinIME.

The organized dictionaries are divided into two parts for the memory usage efficiency.
In the character dictionary, the first file contains characters begins with the stroke "h" or "n" and the second contains characters start with stroke "p", "s", or "z".
In the phrase dictionary, the first file contains phrases whose first character has a unicode value less than 25510. Other phrases are included in the second file.
If a new character or a new phrase is to be added, it should be inserted at the right position of the files according to its frequency.

Default dictionaries included are as follows:
* Character dictionary: *dictSecF_F1.txt*, *dictSecF_F2.txt*, *dictC_F1.txt*, *dictC_F2.txt*.
* Phrase dictionary: *num16bit1.txt*, *num16bit2.txt*, *str1.txt*, *str2.txt*.

Run function strokeDictBuild (defined in strokeDictBuild.cpp) to construct and save the tree file for single character searching.
Run function assocDictBuild (defined in assocDictBuild.cpp) to construct and save the tree file for phrases searching.

To search for single characters, input strokes should consist of characters "h", "s", "p", "n", "z", or "?".
The search result contains characters of the highest frequency that have the matching prefix with the inquery stroke string.
The search guarantees that the fully matched results appear in the output array even if their word frequency is not high enough.
The first candidate is the fully matched character with the highest frequency, if there is any.

To search for phrases, input keywords should be an array of unicode values of characters.
Results consists of words that ensue the inquery words. The words are arranged in an array. The maximum length of characters in a output word is preset.

Ensure that the files *builtTree1.txt*, *builtTree2.txt*, *builtTreeDict1.txt*, *builtTreeDict2.txt* exist before searching.

##Run

Make a copy of the directory.

On Linux operating systems, go to the "stroke-engine/" directory ,run *make test_stroke*, and run *./test_stroke search_stroke*, in which you can replace *search_stroke* with any valid stroke string, e.g. "pz", "n", "h?p". The running time for a 10,000-time-repeated search will be shown (in seconds).

On Windows operating systems, include all .cpp and .h files in an project, compile and run. This should give results in a console window.

##License

The project "ime-stroke" is available under the Apache License, Version 2.0.
