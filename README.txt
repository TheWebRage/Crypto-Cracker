-------------------- Ecryption - David Weber - Version 3.0.1 -------------------- 


This new addition now has a Crypto Cracker menu! This will accept a path to a file to decrypt and another for the output. 


-------------------- Logic ----------------------------

My tool will find the best encryption algorithm from one of the following:
- Ceasar
- Vigenere
- Transpotition

It will also mention when the key is too large or another algorithm was used.

In order to know what algorithm to use, it will:
- Get the distrobutuion for the string
- If the distro looks clear, but offset, then it will use the Ceasar cipher.
- If the distro looks clear, but no offset, then it will use the transposition cipher
	- This will use factors up to size 1000 to create a new 2d array to work in
		- This will rotate the string into a 2d array. 
		- It will Read in going the opposite direction.
		- It will test the new string with the bi-grams to check if it is english
		- if not try the next size factor
	- Otherwise return
- If the distro looks unclear, then:
	- It will try key lengths up to 15
	- It will split the string into xth items into strings 
	- Create a distrobutiuon for these new strings
	- If any of these have a clear distrobution, then use that key length.
		- Find the offset for each string and use ceasar cipher for each
		- Stick them back together and return the key and result
- Otherwise not able to use any of the coded algorithms.

-------------------- How to Compile -------------------- 

1. Create a "build" folder if it doesn't exist.
2. Change directory to the "build" folder.
3. Run "cmake .."
4. Run "make"
5. Finally, to execute the program, run "./Ecryption" to start and use. 


--------------------------------------------------------


--------------------- Results ------------------------
For each of the provided samples, here are my results:

ciphertext1.txt
- Ceasar Cipher
- Key: K - Only took one try to find offset
- Fast Time to recover key
- First bit of decrypted text: 
- CALLMEISHMAELSOMEYEARSAGONEVERMINDHOWLONGPRECISELYHAVINGLITTLEORNOMONEYINMYPURSEANDNOTHINGPARTICULAR

ciphertext2.txt
- Transposition Cipher
- Key: Unable to find key - Tried up to keys 1000.
- Slow time to decrypt


ciphertext3.txt
- Unknown Cipher
- Know it is not one of the ones looking for since it does not have a clear distrobution for any keys up to length 15.
- Slow


ciphertext4.txt
- Vignenere Cipher
- Key: LOGANUTAH - Tried keys up to length 9
- Medium Time to recover
- first bit of decrypted text:
- IAMHAPPYTOJOINWITHYOUTODAYINWHATWILLGODOWNINHISTORYASTHEGREATESTDEMONSTRATIONFORFREEDOMINTHEHISTORYOFOURNATION





































