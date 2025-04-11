/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalbano <dalbano@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:09:30 by dalbano           #+#    #+#             */
/*   Updated: 2025/04/11 15:18:14 by dalbano          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_and_expand_buffer(char *str, int *buffer_size, int j)
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
	return (str);
}

static void	process_variable(t_expansion_context *ctx)
{
	char	*var;
	char	*value;

	ctx->exp.i++;
	var = extract_var_name(ctx->input + ctx->exp.i);
	value = get_env_value(var, ctx->env);
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

static void	handle_current_char(t_expansion_context *ctx)
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
	ctx->new_str = check_and_expand_buffer(ctx->new_str, &ctx->buffer_size,
			ctx->exp.j);
}

char	*expand_variables(char *input, char **env, int lastexitcode)
{
	t_expansion_context	ctx;

	ctx.input = input;
	ctx.env = env;
	ctx.new_str = malloc(100);
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
	return (ctx.new_str);
}
