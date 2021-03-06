// ZihengXu 704756821
// Lab4 
// sfrob.c

#include<stdio.h>
#include<stdlib.h>


int cmp_frob(const void* p1, const void* p2){
	const char* ptr1 = *(const char**)p1;
	const char* ptr2 = *(const char**)p2;
	for(;; ptr1++, ptr2++){
		if (*ptr1 == ' ' && *ptr2 == ' ')
		{
			return 0;
		}
		if (*ptr1 == ' ' || ((*ptr1^42)<(*ptr2^42)))
		{
			return -1;
		}
		if (*ptr2 == ' ' || ((*ptr1^42)>(*ptr2^42)))
		{
			return 1;
		}
	}
}

int main()
{
    char* word; //Holds one word at a time (delimited by spaces)
    char** words; //Array to hold pointers to words
     //curr and next act as current and next iterators to use for noting
    //EOF and auto adding spaces at the end of files
    char curr;
    curr = getchar();
    if(ferror(stdin))
    {
        fprintf(stderr, "Error while reading file!");
        exit(1);
    }
    char next;
    next = getchar();
    if(ferror(stdin))
    {
        fprintf(stderr, "Error while reading file!");
        exit(1);
    }
    word = (char*)malloc(sizeof(char));
    words = (char**)malloc(sizeof(char*));
    int letterIterator = 0;
    int wordsIterator = 0;
    while(curr != EOF) //Read file until EOF
    {
        
        word[letterIterator] = curr; //Add letters to the word
        //Constantly reallocate space for growing words
        char* temp = realloc(word, (letterIterator+2)*sizeof(char));
        if(temp != NULL)
        {
            //Make the word equal to the reallocated space
            word = temp;
        }
        else //Allocation error, print error and exit
        {
            free(word);
            fprintf(stderr, "Error Allocation Memory!");
            exit(1);
        }
        
        
        if(curr == ' ') //Hit the end of the word
        {
            words[wordsIterator] = word; //Add word to words list
            //Constantly reallocate space for growing wordslist
            char** anotherOne = realloc(words, (wordsIterator+2)*sizeof(char*));
            if(anotherOne != NULL)
            {
                //Make words equal to reallocated space
                words = anotherOne;
                wordsIterator++;
                //Set word back to empty by pointing it to other space
                word = NULL;
                word = (char*)malloc(sizeof(char));
                letterIterator = -1; //-1 to bring back to 0 when summed later
            }
            else //Allocation error, print error and exit
            {
                free(words);
                fprintf(stderr, "Error Allocation Memory!");
                exit(1);
            }
        }
        if(next == EOF && curr == ' ')
        {
            break;
        }
        if (curr == ' ' && next == ' ') //Ignore Extra Spaces
        {
            while(curr == ' ')
            {
                curr = getchar();
                if(ferror(stdin))
		  {
		    fprintf(stderr, "Error while reading file!");
		    exit(1);
		  }
            }
            next = getchar();
            if(ferror(stdin))
	      {
		fprintf(stderr, "Error while reading file!");
		exit(1);
	      }
            letterIterator++;
            continue;
        }
        if(next == EOF) //Add a space at the end if there isn't already one
        {
            curr = ' ';
            letterIterator++;
            continue;
        }
        //increment our letter counter and get the next character
        curr = next;
        next = getchar();
        if(ferror(stdin))
	  {
	    fprintf(stderr, "Error while reading file!");
	    exit(1);
	  }
        letterIterator++;
        
    }

//Sort the frobnicated words from our words list
    qsort(words, wordsIterator, sizeof(char*), cmp_frob);
    
    //Output the words to STDOUT using putchar
    for(size_t i = 0; i < wordsIterator; i++)
    {
        for(size_t j = 0; ;j++)
        {
            //EOF error checking
            if(putchar(words[i][j]) == EOF)
            {
                fprintf(stderr, "Error while writing character!");
                exit(1);
            }
            if(words[i][j] == ' ')
            {
                break;
            }
        }
    }
    //De-allocate all the space taken up for the words
    for(size_t i = 0; i < wordsIterator; i++)
    {
        free(words[i]);
    }
    free(words);
    return 0;
}
