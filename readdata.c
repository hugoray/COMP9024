//
// Created by HUGO on 22/1/20.
//

// read file to DDL
void readCollection(DLListStr list) {
    char *fileName = "collection.txt";
    char delim[2] = " ";
    char *token;
    char line[MAX_STRING];

    FILE *fp;

    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("Error!\n");
        return;
    }

    while (fgets(line, MAX_STRING, fp) != NULL) {
        // delete \n
        line[strlen(line) - 1] = '\0';

        /* first token */
        token = strtok(line, delim);

        //int count = 0;
        /* iterate over the rest of the tokens */
        while (token != NULL) {

            // insert token
            insertSetOrd(list, token);

            token = strtok(NULL, delim);
        }

    }

    fclose(fp);
}

// read section 1 to the graph
void readSection1(char **urlname, Graph g, int numberOfurl) {

    char delim[2] = " ";
    char *token;
    char line[MAX_STRING];
    FILE *fp;
    char fileName[MAX_STRING];
    int begin = 0;
    int sign = 0;

    while (begin < numberOfurl) {

        // open the related text file
        strcpy(fileName, urlname[begin]);
        strcat(fileName, ".txt");

        if ((fp = fopen(fileName, "r")) == NULL) {
            printf("ERROR!\n");
            return;
        } else {
            Edge edge;
            edge.v = begin;

            while (fgets(line, MAX_STRING, fp) != NULL) {
                // delete \n
                line[strlen(line) - 1] = '\0';
                // start
                if (strncmp(line, "#start Section-1", 16) == 0) {
                    sign = 1;
                    // break;
                } else if (strncmp(line, "#end Section-1", 14) == 0) {
                    sign = 0;
                    break;
                } else if (sign == 1) {
                    /* first token */
                    token = strtok(line, delim);
                    /* iterate over the rest of the tokens */
                    while (token != NULL) {
                        // check token value
                        int end = 0;
                        while (end < numberOfurl) {
                            // compare to result
                            if (strcmp(urlname[end], token) == 0) {
                                // insert edge
                                edge.w = end;
                                //printf("start url:%s end url: %s \n", urlname[begin],urlname[end]);
                                insertEdge(g, edge);
                                break;
                            }
                            end++;
                        }
                        // continue to get string
                        token = strtok(NULL, delim);
                    }

                }
            }
            begin++;
        }
        fclose(fp);
    }
}

void readSection2(char **urlname, DLListStr invertedList, int numberOfurl) {
    // remove leading and trailing spaces && remove '.' (dot), ',' (comma), ';' (semicolon), ? (question mark)
    char delim[6] = " .,;?";
    char *token;
    char line[MAX_STRING];
    FILE *fp;
    char fileName[MAX_STRING];
    int begin = 0;
    int sign = 0;

    while (begin < numberOfurl) {

        // open the related text file
        strcpy(fileName, urlname[begin]);
        strcat(fileName, ".txt");

        if ((fp = fopen(fileName, "r")) == NULL) {
            printf("ERROR!\n");
            return;
        } else {
            while (fgets(line, MAX_STRING, fp) != NULL) {
                // delete \n
                line[strlen(line) - 1] = '\0';
                // start
                if (strncmp(line, "#start Section-2", 16) == 0) {
                    sign = 1;
                    // break;
                } else if (strncmp(line, "#end Section-2", 14) == 0) {
                    sign = 0;
                    break;
                } else if (sign == 1) {
                    /* first token */
                    token = strtok(line, delim);
                    /* iterate over the rest of the tokens */
                    while (token != NULL) {
                        //  convert all characters to lowercase
                        for (int i = 0; i < strlen(token); i++) {
                            token[i] = tolower(token[i]);
                        }
                        // insert child to list
                        insertChild(invertedList, token, urlname[begin]);
                        // continue to get string
                        token = strtok(NULL, delim);
                    }
                }

            }
        }
        begin++;
    }
    fclose(fp);
}

// read pagerank.txt
void readPagerank(DLListStr L) {

    char delim[3] = " ,";
    char *token;
    char line[MAX_STRING];
    char url[MAX_STRING];

    FILE *fp;
    char *fileName = "pagerankList.txt";
    //int numberOfDegrees = 0;
    double pagerank = 0.0;

    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("Error!\n");
        return;
    }

    //else
    while (fgets(line, MAX_STRING, fp) != NULL) {
        // delete \n
        line[strlen(line) - 1] = '\0';

        int count = 0;
        /* first token */
        token = strtok(line, delim);

        // get the url and pagerank from the text file by using token's index
        while (token != NULL) {
            if (count % 3 == 0) {
                strcpy(url, token);
                url[strlen(token)] = '\0';
            }
            if (count % 3 == 2) {
                pagerank = atof(token);
            }
            token = strtok(NULL, delim);
            count++;
        }
        // insert pagerank to the DLL
        insertDLListPageRank(L, url, pagerank);
    }
    fclose(fp);
}

// read inverted.txt
void readInverted(DLListStr L) {
    char delim[3] = " ,";
    char *token;
    char line[MAX_STRING];
    char word[MAX_STRING];

    FILE *fp;
    char *fileName = "invertedIndex.txt";


    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("Error!\n");
        return;
    }
    while (fgets(line, MAX_STRING, fp) != NULL) {
        // delete \n
        line[strlen(line) - 1] = '\0';

        int count = 0;
        /* first token */
        token = strtok(line, delim);
        while (token != NULL) {
            if (count == 0) {
                strcpy(word, token);
                word[strlen(token)] = '\0';
            } else {
                // insert page rank
                insertChild(L, word, token);
            }
            // continue to get string
            token = strtok(NULL, delim);
            count++;
        }
    }
}