#include "shell.h"
#include "dbg.h"
#include <stdarg.h>

int Shell_exec(Shell template, ...){
	apr_pool_t *p = NULL;
	int rc = -1;
	apr_status_t rv = APR_SUCCESS;
	va_list argp;
	const char *key = NULL;
	const char *arg = NULL;
	int i = 0;
	
	int repl = 0;	// Ch2
	
	rv = apr_pool_create(&p, NULL);
	check(rv == APR_SUCCESS, "Failed to create pool%c", '.');
	
	va_start(argp, template);
	
	for( key = va_arg(argp, const char *); 
		 key != NULL; 
		 key = va_arg(argp, const char *) ) {
		arg = va_arg(argp, const char *);
		
		//debug("k:%s, a: %s ", key, arg); // DEBUG
		for( i = 0; template.args[i] != NULL; i++){
			//debug(" to: %s", template.args[i]); // DEBUG
			if(strcmp(template.args[i], key) == 0) {
				template.args[i] = arg;
				//debug(" i:%d, t: %s", i, template.args[i]); // DEBUG
				repl++;	// Ch2
				break; // found it
			}
		}
	}
	//debug("---END---\n"); // debug
	//debug("args: %d", CURL_SH.arg_repl);
	check(repl == template.arg_repl, 
		"Wrong count of arguments (%d of %d) given for %s", 
		repl, template.arg_repl, template.exe); 	// Ch2
		
	rc = Shell_run(p, &template); // DEBUG
	apr_pool_destroy(p);
	va_end(argp);
	return rc;
	
error:
	if(p) {
		apr_pool_destroy(p);
	}
	return rc;
}

int Shell_run(apr_pool_t *p, Shell *cmd) {
	apr_procattr_t *attr;
	apr_status_t rv;
	apr_proc_t newproc;

	rv = apr_procattr_create(&attr, p);
	check(rv == APR_SUCCESS, "Failed to create proc attr%c", '.');
	
	rv = apr_procattr_io_set(attr, APR_NO_PIPE, APR_NO_PIPE,
	 	APR_NO_PIPE);
	check(rv == APR_SUCCESS, "Failed to set IO of command%c", '.');
	
	rv = apr_procattr_dir_set(attr, cmd->dir);
	check(rv == APR_SUCCESS, "Failed to set root to %s", cmd->dir);
	
	rv = apr_procattr_cmdtype_set(attr, APR_PROGRAM_PATH);
	check(rv == APR_SUCCESS, "Failed to set cmd type%c", '.');
	
	rv = apr_proc_create(&newproc, cmd->exe, cmd->args, NULL, 
		attr, p);
	check(rv == APR_SUCCESS, "Failed to run command%c", '.');
	
	rv = apr_proc_wait(&newproc, &cmd->exit_code, &cmd->exit_why,
		 APR_WAIT);
	check(rv == APR_CHILD_DONE, "Failed to wait%c", '.');
	
	check(cmd->exit_code == 0, "%s exited badly.", cmd->exe);
	check(cmd->exit_why == APR_PROC_EXIT, "%s was killed or crashed", cmd->exe);
	
	return 0;
	
error:
	return -1;
}

Shell CLEANUP_SH = {
	.exe = "rm",
	.dir = "/tmp",
	.args = {"rm", "-rf", "/tmp/pkg-build", "/tmp/pkg-src.tar.gz",
		"/tmp/pkg-src.tar.bz2", "/tmp/DEPENDS", NULL},
	.arg_repl = 0 	// Ch2
};

Shell GIT_SH = {
	.exe = "git",
	.dir = "/tmp",
	.args = {"git", "clone", "URL", "pkg-build", NULL},
	.arg_repl = 1 	// Ch2
};

Shell TAR_SH = {
	.exe = "tar",
	.dir = "/tmp/pkg-build",
	.args = {"tar", "-xzf", "FILE", "--strip-components", "1", NULL},
	.arg_repl = 1 	// Ch2
};

Shell CURL_SH = {
	.exe = "curl",
	.dir = "/tmp",
	.args = {"curl", "-L", "-o", "TARGET", "URL", NULL},
	.arg_repl = 2 	// Ch2
};

Shell CONFIGURE_SH = {
	.exe = "./configure",
	.dir = "/tmp/pkg-build",
	.args = {"configure", "OPTS", NULL},
	.arg_repl = 1 	// Ch2
};

Shell MAKE_SH = {
	.exe = "make",
	.dir = "/tmp/pkg-build",
	.args = {"make", "OPTS", NULL},
	.arg_repl = 1 	// Ch2
};

Shell INSTALL_SH = {
	.exe = "sudo",
	.dir = "/tmp/pkg-build",
	.args = {"sudo", "make", "TARGET", NULL},
	.arg_repl = 1 	// Ch2
};


