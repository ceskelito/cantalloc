# cantalloc

A basic C garbage collector system. Call cantalloc()/ccantalloc() instead of malloc()/calloc() to allocate memory. Then, forget about your pointers and just call cantalloc_clean() at the end of your program to free everything. No leaks, no stress. Have a nice day!


## Example

<img width="497" alt="Screen Shot 2023-02-04 at 2 14 54 PM" src="https://user-images.githubusercontent.com/95633668/216769739-afd10d33-86ff-4fad-8820-ba0f3e1110fe.png">




Output:

<img width="180" alt="Screen Shot 2023-02-04 at 1 17 51 PM" src="https://user-images.githubusercontent.com/95633668/216767370-1b619b09-5fb4-4719-85b1-f44a44c51a4a.png">


<img width="494" alt="Screen Shot 2023-02-04 at 1 18 11 PM" src="https://user-images.githubusercontent.com/95633668/216767374-17eb0d92-081e-46a1-9f9d-0d6409174c74.png">
