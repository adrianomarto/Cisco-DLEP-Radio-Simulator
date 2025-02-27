/*------------------------------------------------------------------
 * cli.h -- embedded command line interpreter  
 *
 * Copyright (C) 2009 by B. Berry
 * All rights reserved. 
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *------------------------------------------------------------------
 */

#ifndef __CLI_H__
#define __CLI_H__

#include <inttypes.h>

/*
 * Public directories that applications can register with.
 * Enable define for these root directories.  Once defined,
 * apps can register in this directory structure.  If not,
 * applications register to the root directory. 
 */
#define CLI_ROOT_DIRS     ( 1 )

   
/*  
 * This is the maximum number of parameters that can be passed
 * to the application function.  The parameters are passed to
 * the application in the argument count and argument value
 * format. 
 */ 
#define ARGC_MAX    ( 11 ) 


/*
 * Number of characters in an entry's name, for directories
 * and commands
 */
#define CLI_ENTRY_LEN    ( 34 )


/* 
 * return codes 
 */  
typedef enum {
    RC_CLI_OK = 0,
    RC_CLI_NULL_NAME,
    RC_CLI_NULL_FV,
    RC_CLI_DUPLICATE,
    RC_CLI_RECORD_CORRUPT,
    RC_CLI_NULL_CMD,
    RC_CLI_DIR_INVALID,
} RC_CLI_t;



/*
 * type def for call back function to process user command parsers
 */
typedef void (*cli_funcvar_t)(uint32_t argc, char *argv[]);


/*
 * The structure for a directory or command entry.
 */
typedef struct t_nodal_record {
    struct t_nodal_record  *cmd_list;  
    char                   name[CLI_ENTRY_LEN+1];
    cli_funcvar_t          fv;
    struct t_nodal_record  *parent_dir;
    struct t_nodal_record  *next_entry;
    struct t_nodal_record  *link2subdir;
} cli_record_t;



/*
 * A few common root command directories
 * if enabled. 
 */
#ifdef CLI_ROOT_DIRS 
extern cli_record_t cli_config_dir;
extern cli_record_t cli_show_dir;
extern cli_record_t cli_clear_dir;
//extern cli_record_t cli_operation_dir;
extern cli_record_t cli_debug_dir;
extern cli_record_t cli_test_dir;
#endif


/*
 * The structure required to initialize the CLI facility.
 * It must be initialized before use.
 */
typedef struct {
    char  prefix[CLI_ENTRY_LEN];
} cli_init_data_t;



/*
 * prototypes
 */

/* add a command */
extern RC_CLI_t cli_mkcmd(char  *name,
               cli_funcvar_t  fv,
               cli_record_t *dir_rec,
               cli_record_t *cmd_rec);


/* make a directory */
extern RC_CLI_t cli_mkdir(char  *name,
               cli_record_t  *dir_rec,
               cli_record_t  *sub_dir);


/* drive the cli */   
extern void cli_engine(char *input_string); 


/* set the prompt string */ 
void cli_set_prompt(char *prompt); 


/* init function */
extern RC_CLI_t cli_init(cli_init_data_t *init_data);

#endif  /*  __CLI_H__  */

