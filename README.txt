
COMPILATION:
------------------------------------------------------------------------------------------------------------------------------

1.  Open command prompt inside the Disease Monitor folder.
2.  Type make and press enter.
3.  The executable is the file named "runner" inside the Disease Monitor folder.

EXAMPLE COMMANDS:
------------------------------------------------------------------------------------------------------------------------------

You can use the following command to test the application:
./runner -p ./Data\ Files/patientRecordsFile.txt -h1 5 -h2 4 -b 520

The parameters can be given in any preferred order. So the following is equivalent to the example command:
./runner -h2 4 -h1 5 -b 520 -p ./Data\ Files/patientRecordsFile.txt

After the application has processed the input files, the following command can be used:

[*] /globalDiseaseStats [date1 date2]
..............................................................................................................................
        The application prints for every disease, the number of hits that have been recorded by the system. If the date1 and
        date2 are given, then the application will print for every disease, the number of hits that have been recorded by the
        system during the time period [date1...date2].
        If [date1] has been defined there must also be a definition for [date2], otherwise an error will be given to the user.
..............................................................................................................................

[*] /diseaseFrequency virusName [country] date1 date2
..............................................................................................................................
        If the [country] argument is not given, the application prints for the disease virusName the number of hits that have
        been recorded by the system during the period [date1...date2]. If the [country] is given as argument, the application
        will print for the disease virusName, the number of hits in the country [country] that have been recorded during the
        period [date1...date2].
..............................................................................................................................

[*] /topk-Diseases k country [date1 date2]
..............................................................................................................................
        The application will print, for the country given the diseases that have the top k number of hits during the period
        [date1 date2] when given. If there is a definition for [date1] there must be a definition for [date2], otherwise an
        error will be given to the user.
..............................................................................................................................

[*] /topk-Countries k disease [date1 date2]
..............................................................................................................................
        The application will print, for the disease the countries that have the top k number of hits for the same disease.
..............................................................................................................................

[*] /insertPatientRecord recordID patientFirstName patientLastName diseaseID countryID entryDate [exitDate]
..............................................................................................................................
        The application will add to the system a new record with its attributes. The attribute [exitDate] is optional.
..............................................................................................................................

[*] /recordPatientExit recordID exitDate
..............................................................................................................................
        The application will add the exitDate to the record with ID recordID.
..............................................................................................................................

[*] /numCurrentPatients [disease]
..............................................................................................................................
        If the argument [disease] is given, the application will print the number of patients that are still hospitalized with
        the disease. If no argument is given, the application will print for every disease, the records of the patients that
        are still hospitalized.
..............................................................................................................................

[*] /exit
..............................................................................................................................
        Exit from the application.
..............................................................................................................................

DESIGNING DECISIONS:
------------------------------------------------------------------------------------------------------------------------------

- PARSING COMMAND LINE ARGUMENTS -
To parse the arguments given in the command line at the start of the application, the function "get_opt_long_only" is used
which needs a static struct option array (long_options[]) to be defined and it is implemented in the <getopt.h> header file.
During the parsing the arguments are passed to variables inside the application, so they can be used for later.


- STRUCTURES -
All structures used are implemented in classes and are split on files depending on how relative they are to one another.
We have a LINKED LIST to hold the patient records, one HASHTABLE with the country as key, one HASHTABLE with the disease as
key and for each key in any hashtable a RED BLACK TREE with the entry date as key.

- GLOBAL DISEASE STATS -
It is first called on the hashtable for diseases, then goes to the level of BUCKET and then BUCKETRECORD in order to be
called by the tree for the disease. Inside the tree there is a variable stored for the size, which means the nodes that belong
to it. The size of the root of the tree is essentially the number of hits of the disease. When dates are given, the function
calls a variation of it that recursively searches the tree for dates during the period given and returning the number found.

All other commands follow the same logic in call order (hashtable -> bucket -> bucketrecord -> tree).

- DISEASE FREQUENCY -
The function of the tree level recursively searches the tree and counts the hits during the period given and for the country
given. If no country is given, the procedure is the same as for the global_disease_stats function, so that is called instead.

- TOP K DISEASES -
Is called by the hashtable for countries. When in tree level it uses a LIST called LLTree that holds the disease and how many
times it has been added by the resurse tree search. Then that list uses a function to find the diseases with top k counts
on the diseases and print them.

- TOP K COUNTRIES -
Follows the same logic as topk_diseases but is called by the hashtable for diseases.

- INSERTION TO HASHTABLE -
The hashtable holds buckets(number is defined by the user) and each bucket has a size. For easier insertion to the bucket,
space for bucket_records is allocated when the hashtable is created. The number of bucket_records to be held is known and
the number of bucket_records that are held is in a variable inside the bucket class. When an item is inserted, the insert
makes a new bucket_record for it.

- NUM CURRENT PATIENTS -
Is called by the hashtable for diseases. There are two implementations for the bucket_record level: num_current_patients_1
will print the records, num_current_patients_2 will print the number of records during the period given. Both go all the
way down to tree level. The second uses recursion to count the patients and return their number. The first uses a LIST
called LNTree that holds records. In the tree, when searched recursively, if a record without an exitDate is found, then
it will be added to the list. When all search is done, num_current_patients is called to print the list of records.
