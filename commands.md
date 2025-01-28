# Editor

| Keys               | Control             |
|--------------------|---------------------|
| Arroys, j, k, i, l | Move cursor         |
| s                  | Toggle Selection    |
| [0-9][a-f]         | Hex Insert (nibble) |

# Command line 

| Key | Description          |
|-----|----------------------|
|  :  | Open command line    |
|  ;  | Clear command output |

| Command                             | Description                 |
|-------------------------------------|-----------------------------|
| :q                                  | Quit                        | 
| :m[bnm]                             | Place marker                |
| :mr                                 | Remove marker               |
| :jp &lt;N&gt;                       | Jump **N** bytes            |
| :gt &lt;addr|end|eof&gt;            | Go to address               |
| :s &lt;text&gt;                     | Insert string/text          |
| :next &lt;"text"|*hex sequence*&gt; | Jump to the next match      |
| :select &lt;byte count&gt;          | Selects **N** bytes         |
| :mv &lt;amount&gt;                  | Move cursor (and selection) |
