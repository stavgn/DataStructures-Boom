int main(int argc, const char**argv) {

    char buffer[MAX_STRING_INPUT_SIZE];
    FILE *fd = fopen("in2.txt", "r");
    if(!fd)
    {
        return printf("Sux to b u");
    }
    // Reading commands
    while (fgets(buffer, MAX_STRING_INPUT_SIZE, fd) != NULL) {
        fflush(stdout);
        if (parser(buffer) == error)
            break;
    };
    return 0;
}

static errorType OnGetMostViewedClasses(void* DS, const char* const command) {
    int numOfClasses = 0;
    int *courses = NULL, *classes = NULL;
	StatusType res = SUCCESS;

	ValidateRead(sscanf(command, "%d", &numOfClasses), 1, "%s failed.\n", commandStr[GETMOSTVIEWEDCLASSES_CMD]);
	if (numOfClasses > 0) {
		courses = (int *)malloc(numOfClasses * sizeof(int));
		classes = (int *)malloc(numOfClasses * sizeof(int));
		if (courses == NULL || classes == NULL) {
		res = ALLOCATION_ERROR;
		}
	}

	if (res != ALLOCATION_ERROR) {
		res = GetMostViewedClasses(DS, numOfClasses, courses, classes);
	}

    if (res != SUCCESS) {
        printf("%s: %s\n", commandStr[GETMOSTVIEWEDCLASSES_CMD], ReturnValToStr(res));
		if (courses != NULL) free(courses);
		if (classes != NULL) free(classes);
        return error_free;
    }

    printf("%s: %s\n", commandStr[GETMOSTVIEWEDCLASSES_CMD], ReturnValToStr(res));

	printf("Course\t|\tClass\n");

    for (int i = 0; i < numOfClasses; i++)
    {
        printf("%d\t|\t%d\n", courses[i], classes[i]);
    }

    printf("--End of most viewed classes--\n");

	if (courses != NULL) free(courses);
	if (classes != NULL) free(classes);

    return error_free;
}