#define PY SSIZE_T_CLEAN
#include <Python.h>
#include <conwayssoldiers.h>


#define DEBUG_MESSAGES 1
#define DEBUG_LOG if(DEBUG_MESSAGES)

#define SAVE_DIR_PATH "./cwssaves/"

static PyObject *cws_deleteSaves(PyObject *self, PyObject *args)
{
	char command[1024];
	strcpy(command, "rm -r ");
	strcat(command, SAVE_DIR_PATH);
	strcat(command, "*.txt");
	system(command);
	Py_RETURN_NONE;
}



static PyObject *cws_initBoard(PyObject *self, PyObject *args)
{
	char *playername;
	char filename[1024];
	FILE *fp;
	struct conwayssoldiers_game_s cwg;
	
	if(!PyArg_ParseTuple(args, "s", &playername))
	{
		return NULL;
	}
	strcpy(filename, SAVE_DIR_PATH);
	strcat(filename, playername);
	strcat(filename, ".txt");
	
	
	fp = fopen(filename, "w");
	if(fp != NULL)
	{
		conwayssoldiers_initBoard(&cwg, 'o');
		fprintf(fp, "%d\n", cwg.numberOfMoves);
		for(int j = 9; j >= 0; j--)
		{
			for(int i = 0; i < 20; i++)
			{
				fprintf(fp, "%d,", cwg.board[i][j]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
		DEBUG_LOG printf("\nCWS: File succsesfuly written\n");

	}
	else
	{
		printf("\nCWS: File: %s :failed to open\n", filename);
		return NULL;
	}
		
	Py_RETURN_NONE;
}


static PyObject *cws_renderFull(PyObject *self, PyObject *args)
{
	char *playername;
	char filename[1024];
	FILE *fp;
	struct conwayssoldiers_game_s cwg;
	
	if(!PyArg_ParseTuple(args, "s", &playername))
	{
		return NULL;
	}
	strcpy(filename, SAVE_DIR_PATH);
	strcat(filename, playername);
	strcat(filename, ".txt");
	
	
	fp = fopen(filename, "r");
	if(fp != NULL)
	{
		fscanf(fp, "%d ", &(cwg.numberOfMoves));
		for(int j = 9; j >= 0; j--)
		{
			for(int i = 0; i < 20; i++)
			{
				int buf = 0;
				fscanf(fp, "%d,", &buf);
				cwg.board[i][j] = (char)buf;
			}
		}
		fclose(fp);
	}
	else
	{
		printf("\nCWS: File: %s :failed to open\n", filename);
		return NULL;
	}
	conwayssoldiers_renderFullBoard(&cwg);
	DEBUG_LOG printf("\nDebug\n%s\n\n", cwg.boardString);
	
	
	char test[] = {(char)192, '\0'};
	return PyUnicode_FromString(test);
}



static PyObject *cws_renderShort(PyObject *self, PyObject *args)
{
	char *playername;
	char filename[1024];
	FILE *fp;
	struct conwayssoldiers_game_s cwg;
	
	if(!PyArg_ParseTuple(args, "s", &playername))
	{
		return NULL;
	}
	strcpy(filename, SAVE_DIR_PATH);
	strcat(filename, playername);
	strcat(filename, ".txt");
	
	
	fp = fopen(filename, "r");
	if(fp != NULL)
	{
		fscanf(fp, "%d ", &(cwg.numberOfMoves));
		for(int j = 9; j >= 0; j--)
		{
			for(int i = 0; i < 20; i++)
			{
				int buf = 0;
				fscanf(fp, "%d,", &buf);
				cwg.board[i][j] = (char)buf;
			}
		}
		fclose(fp);
	}
	else
	{
		printf("\nCWS: File: %s :failed to open\n", filename);
		return NULL;
	}
	conwayssoldiers_renderCompactBoard(&cwg);
	DEBUG_LOG printf("\nCWS Debug\n%s\n\n", cwg.boardString);
	
	
	return PyUnicode_FromString(cwg.boardString);
}


static PyObject *cws_moveSoldier(PyObject *self, PyObject *args)
{
	
	char *playername;
	char filename[1024];
	FILE *fp;
	struct conwayssoldiers_game_s cwg;
	
	int x, y;
	char* xpt;
	char* directionpt;
	char direction;
	
	if(!PyArg_ParseTuple(args, "ssis", &playername, &xpt, &y, &directionpt))
	{
		return NULL;
	}
	strcpy(filename, SAVE_DIR_PATH);
	strcat(filename, playername);
	strcat(filename, ".txt");
	
	
	fp = fopen(filename, "r");
	if(fp != NULL)
	{
		fscanf(fp, "%d ", &(cwg.numberOfMoves));
		for(int j = 9; j >= 0; j--)
		{
			for(int i = 0; i < 20; i++)
			{
				int buf = 0;
				fscanf(fp, "%d,", &buf);
				cwg.board[i][j] = (char)buf;
			}
		}
		fclose(fp);
	}
	else
	{
		printf("\nCWS: File: %s :failed to open\n", filename);
		return NULL;
	}
	
	direction = directionpt[0];
	x = toupper(xpt[0])-65;
	conwayssoldiers_moveSoldier(x, y, direction, &cwg);
	
	fp = fopen(filename, "w");
	if(fp != NULL)
	{
		fprintf(fp, "%d\n", cwg.numberOfMoves);
		for(int j = 9; j >= 0; j--)
		{
			for(int i = 0; i < 20; i++)
			{
				fprintf(fp, "%d,", cwg.board[i][j]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
		DEBUG_LOG printf("\nCWS: File succsesfuly written\n");

	}
	else
	{
		printf("\nCWS: File: %s :failed to open\n", filename);
		return NULL;
	}

	conwayssoldiers_renderCompactBoard(&cwg);
	DEBUG_LOG printf("\nCWS Debug\n%s\n\n", cwg.boardString);

	return PyUnicode_FromString(cwg.boardString);
}


static PyMethodDef cwsMethods[] = {
	{"deleteSaves", cws_deleteSaves, METH_VARARGS, "Deletes all the save txt files in the save directory"},
	{"initBoard", cws_initBoard, METH_VARARGS, "Python interface for the conways soldiers init method"},
	{"renderFull", cws_renderFull, METH_VARARGS, "Python interface for the conways soldiers render full board method"},
	{"renderShort", cws_renderShort, METH_VARARGS, "Python interface for the conway soldiers render shor board method"},
	{"moveSoldier", cws_moveSoldier, METH_VARARGS, "Python interface for the conway soldiers move soldier method"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef cwsmodule = {
	PyModuleDef_HEAD_INIT,
	"cws",
	"Python interface for the conways soldier c libary",
	-1,
	cwsMethods
};

PyMODINIT_FUNC PyInit_cws(void)
{
	char command[1024];
	strcpy(command, "mkdir ");
	strcat(command, SAVE_DIR_PATH);
	system(command);
	return PyModule_Create(&cwsmodule);
}
