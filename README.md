# minishell
Rewrite a shell

Shell should:
- Show a promt when waiting for a new command.
- Search and launch the right executable (based on PATH variable or by using relative or ablosute path like in bash).
- It must implement the builtins like in bash:
  - echo with option "-n".
  - cd with only relative or absolute path.
  - pwd without any options.
  - export without any options.
  - unset without any options.
  - env without any options and arguments.
  - exit without any options.
- ; in the command should separate commands like in bash.
- ' and " should work like in bash except for multiline commands.
- Redirections > < >> should work like in bash except for descriptor aggrigation.
- Pipes | should work like in bash.
- Environment variables ($ followed by charactes) should work like in bash.
- $? should work like in bash.
- ctrl-X, ctrl-D and ctrl-\ should have the same result as in bash.

Bonus part:
- Added possibility to move the coursor left and right and edit the command line.
- Added command history.
- Added possibility to move directly by word towards the left and or the right using "page up" and "page down".
- Added possibility to go directly to the beggining or the end of a line by pressing "home" and "end".

To compile the project use "make".
To compile with the bonus part use "make bonus".
