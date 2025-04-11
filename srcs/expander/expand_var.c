#include "minishell.h"

char *replace_env_var(char *input, char **env, int lastexitcode)
{
    char *var_name;
    char *value;

    if (!input || input[0] != '$') 
        return ft_strdup(input);
    
    if (strcmp(input, "$?") == 0) 
    {
        char *exit_code_str = malloc(12);
        if (!exit_code_str)
            return NULL;
        sprintf(exit_code_str, "%d", lastexitcode); 
        return exit_code_str;
    }

    var_name = input + 1; 
    value = get_env_value(var_name, env);

    if (value) 
        return value;
    else 
        return ft_strdup("");
}


char *extract_var_name(char *input)
{
    int i = 0;

    if (!input || !input[i] || !(ft_isalpha(input[i]) || input[i] == '_'))
        return ft_strdup(""); 

    while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
        i++;

    return strndup(input, i); 
}

void int_to_str(int num, char *str)
{
    int i = 0;
    if (num == 0)
    {
        str[i++] = '0';
    }
    else
    {
        int temp = num;
        int length = 0;
        while (temp != 0)
        {
            temp /= 10;
            length++;
        }
        str[length] = '\0';
        while (num != 0)
        {
            str[--length] = (num % 10) + '0';
            num /= 10;
        }
    }
}

static char *check_and_expand_buffer(char *str, int *buffer_size, int j)
{
    if (j >= *buffer_size - 10)  
    {
        *buffer_size *= 2; 
        str = ft_realloc(str, *buffer_size);  
        if (!str)
        {
            perror("realloc failed");
            exit(1);
        }
    }
    return str; 
}
static void process_variable(t_expansion_context *ctx)
{
    ctx->exp.i++; 
    char *var = extract_var_name(ctx->input + ctx->exp.i); 
    char *value = get_env_value(var, ctx->env);          
    
    if (value)
    {
        ft_strcpy(ctx->new_str + ctx->exp.j, value);        
        ctx->exp.j += ft_strlen(value);                     
    }
    else
    {
        ctx->new_str[ctx->exp.j++] = '$';                   
        ft_strcpy(ctx->new_str + ctx->exp.j, var);
        ctx->exp.j += ft_strlen(var);
    }
    ctx->exp.i += ft_strlen(var);                          
    free(var);
    free(value);
}
static void handle_current_char(t_expansion_context *ctx)
{
    if (ctx->input[ctx->exp.i] == '$' && !ctx->exp.in_single_quotes)
    {
        if (ctx->input[ctx->exp.i + 1] == '?')
        {
            ft_strcpy(ctx->new_str + ctx->exp.j, ctx->exit_code_str); 
            ctx->exp.j += ft_strlen(ctx->exit_code_str);
            ctx->exp.i += 2;
        }
        else
            process_variable(ctx);  
    }
    else
        ctx->new_str[ctx->exp.j++] = ctx->input[ctx->exp.i++];
    ctx->new_str = check_and_expand_buffer(ctx->new_str, &ctx->buffer_size, ctx->exp.j);
}
char *expand_variables(char *input, char **env, int lastexitcode)
{
    t_expansion_context ctx;
    ctx.input = input;
    ctx.env = env;
    ctx.buffer_size = 100;
    ctx.new_str = malloc(ctx.buffer_size);
    if (!ctx.new_str)
    {
        perror("malloc failed");
        exit(1);
    }
    ctx.exp.i = 0;
    ctx.exp.j = 0;
    ctx.exp.in_single_quotes = 0;
    ctx.exp.in_double_quotes = 0;
    int_to_str(lastexitcode, ctx.exit_code_str);
    while (ctx.input[ctx.exp.i])
    {
        if (ctx.input[ctx.exp.i] == '\'')
            ctx.exp.in_single_quotes = !ctx.exp.in_single_quotes;
        else if (ctx.input[ctx.exp.i] == '"')
            ctx.exp.in_double_quotes = !ctx.exp.in_double_quotes;
        handle_current_char(&ctx);
    }
    ctx.new_str[ctx.exp.j] = '\0';
    return ctx.new_str;
}
