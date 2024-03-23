# Jade Moon Grammar

## Legend
> _?_ - zero or one occurrences
>
> _*_ - zero or more occurrences
>
> _+_ - one or more occurrences

## Grammar Rules

### NUMBER
> [0-9]

### ALPHA
> [a-zA-Z]

### CONSTANT
> **NUMBER**_+_

### IDENTIFIER
> (```_``` | **ALPHA**) ( ```_``` | **ALPHA** | **NUMBER**)_*_

### SCOPE_IDENTIFIER
> **IDENTIFIER** (```::``` **IDENTIFIER**)*

### TYPE_DECORATOR
> ```const```_?_ (```ref``` | ```ptr```)_?_

### FUNCTION_POINTER
> ```fn_ptr``` ```(``` **FUNCTION_PTR_ARGS** ```)``` ```->``` **TYPE**

### FUNCTION_PTR_ARGS
> **TYPE** (```,``` **TYPE**)_*_

### BASE_TYPE
> (**SCOPE_IDENTIFIER** **TEMPLATE**_?_) | **FUNCTION_POINTER**

### TYPE
> **TYPE_DECORATOR*** **BASE_TYPE**

### VARIABLE
> ```var``` **IDENTIFIER** ```:``` **TYPE** (```=``` **EXPR**)_?_ ```;```

### TEMPLATE
> ```<``` **TEMPLATE_LIST** ```>```

### TEMPLATE_LIST
> **IDENTIFIER** (```,``` **TEMPLATE_LIST**)_*_

### FUNCTION
> ```fn``` **IDENTIFIER** **TEMPLATE**_?_ ```(``` **FUNCTION_ARGS_LIST** ```)``` ```->``` **TYPE_BLOCK**

### FUNCTION_ARGS_LIST
> **FUNCTION_ARG** (```,``` **FUNCTION_ARG**)_*_

### FUNCTION_ARG
> **IDENTIFIER** ```:``` **TYPE**

### STRUCTURE
> ```struct``` **IDENTIFIER** **TEMPLATE**_?_ **STRUCT_BLOCK**

### STRUCT_BLOCK
> ```{``` **STRUCT_VARIABLES** ```}```

### STRUCT_VARIABLES
> **IDENTIFIER** ```:``` **TYPE** ```;``` **STRUCT_VARIABLES**_?_

### WHILE_STMT
> ```while``` ```(``` **EXPR** ```)``` (**SINGLE_STMT** | **BLOCK_STMT**)

### IF_STMT
> ```if``` ```(``` **EXPR** ```)``` (**SINGLE_STMT** | **BLOCK_STMT**)

### SINGLE_STMT
> ```:``` **STMT**

### BLOCK_STMT
> ```{``` **STMT*** ```}```

### STMT
> **WHILE_STMT** | **IF_STMT**

### NAMESPACE
> ```namespace``` **IDENTIFIER** **TOP_STMT_BLOCK**

### TOP_STMT_BLOCK
> ```{``` **TOP_STMT*** ```}```

### TOP_STMT
> **VARIABLE** | **FUNCTION** | **STRUCT**

### EXPR
> **UNARY_OPERATOR*** **SCOPED_IDENTIFIER** (**CALL** | **ACCESS**)* (**INFIX_OPERATOR** **EXPR**)?

### CALL
> **TEMPLATE_CALL** ```(``` **CALL_ARGS** ```)```

### CALL_ARGS
> **EXPR** (```,``` **EXPR**)*

### TEMPLATE_CALL
> (```::``` **TEMPLATE**)? **CALL**

### UNARY_OPERATOR
> ```!``` | ```&``` | ```~``` | ```*```

### POSTFIX_OPERATOR
> ```.``` | ```->```

### ACCESS
> **POSTFIX_OPERATOR** **IDENTIFIER** **CALL***

### INFIX_OPERATOR
> ```+``` | ```-``` | ```*``` | ```/```