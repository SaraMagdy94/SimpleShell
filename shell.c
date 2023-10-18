i#include "main.h"
/**
 *  * token - A function that executes a command.
 *   * execute - A function that executes a command.
 *    * @r: A pointer to a string containing the command to be executed.
 *     * @a: A pointer to a string containing the command to be executed.
 *
 *     */
void token(char *r, char *a[]) {
	    int i = 0;
	        char *t = strtok(r, " \t\n;");
		
		    while (t != NULL && i < BUFFER_SIZE) {
			            a[i++] = t;
				            t = strtok(NULL, " \t\n;");
					        }
		    
		        a[i] = NULL;
}

void execute(char *a[]) {
	    pid_t p = fork();
	    
	        if (p == -1) {
			        perror("fork");
				        exit(EXIT_FAILURE);
					    }
		    else if (p == 0) {
			            execvp(a[0], a);
				            perror("execvp");
					            exit(EXIT_FAILURE);
						        }
		        else {
				        int s;
					        wait(&s);
						    }
}
void execute_commands(char *commands[]) {
	    int i = 0;
	        while (commands[i] != NULL) {
			        char *args[BUFFER_SIZE];
				        token(commands[i], args);
					
					        if (args[0] != NULL) {
							            execute(args);
								            }
						
						        i++;
							    }
}

void execute_commands_interactive(char *commands[]) {
	    int i = 0;
	        int result = 0;
		
		    while (commands[i] != NULL) {
			            char *args[BUFFER_SIZE];
				            token(commands[i], args);
					    
					            if (args[0] != NULL) {
							                pid_t p = fork();
									
									            if (p == -1) {
											                    perror("fork");
													                    exit(EXIT_FAILURE);
															                }
										                else if (p == 0) {
													                execvp(args[0], args);
															                perror("execvp");
																	                exit(EXIT_FAILURE);
																			            }
												            else {
														                    int s;
																                    wait(&s);
																		    
																		                    if (WIFEXITED(s)) {
																					                        result = WEXITSTATUS(s);
																								                }
																				                }
													            }
						    
						            if (strstr(commands[i], "&&") && result != 0) {
								                break;
										        }
							            else if (strstr(commands[i], "||") && result == 0) {
									                break;
											        }
								    
								            i++;
									        }
}i
