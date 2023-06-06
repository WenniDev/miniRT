#*********PROJECT**********#

PROJDIR	=	$(realpath $(CURDIR))
NAME	=	miniRT
LIBDIR	=	$(PROJDIR)/lib
SRCDIR	=	$(PROJDIR)/srcs
HDDIR	=	$(PROJDIR)/inc
OBJDIR	=	$(PROJDIR)/objs
DEPDIR	=	$(PROJDIR)/deps

#*********FILES************#

LIBFT	=	$(LIBDIR)/libft/libft.a
LIBMLX	=	$(LIBDIR)/minilibx/libmlx.a
SRCS	=	$(SRCDIR)/draw_circle.c
HD		=	$(HDDIR)/miniRT.h
OBJS	=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
DEPS	=	$(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.d))

#*********COMPILER*********#

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
DEBUG	=	-g -fsanitize=address
HDINC	=	-I $(HDDIR) -I $(LIBDIR)/libft/inc -I $(LIBDIR)/minilibx
LIBINC	=	-L $(LIBDIR)/minilibx -lm -lmlx -lXext -lX11

#*********COLORS***********#

GREEN	=	\e[32m
BLUE	=	\e[34m
NC		=	\e[0m

#*********RULES************#

all : $(NAME)

debug : $(NAME)
	@printf "Linking $(BLUE)$< $(NC)with debug flags\n"
	@$(CC) $(CFLAGS) $(DEBUG) $(OBJS) $(LIBFT) -o $(NAME) $(LIBINC)
	@printf "$(GREEN)Done\n$(NC)"

$(NAME) : $(LIBFT) $(OBJS)
	@printf "$(GREEN)Build complete\n$(NC)"
	@printf "Linking $(BLUE)$@\n$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $@ $(LIBINC)
	@printf "$(GREEN)Done\n$(NC)"

$(LIBFT) :
	@printf "Compiling $(notdir $@)\n"
	@make -s -C $(LIBDIR)/libft/
	@printf "$(GREEN)Done\n$(NC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $@))
	@printf "Building $(BLUE)$(notdir $@)\n$(NC)"
	@$(CC) $(CFLAGS) $(HDINC) -c $< -o $@ \
		-MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))

-include $(DEPS)

clean :
	@printf "Cleaning object files...\n"
	@make -s clean -C $(LIBDIR)/libft/
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)Done\n$(NC)"
	@printf "Cleaning dependency files...\n"
	@rm -rf $(DEPDIR)
	@printf "$(GREEN)Done\n$(NC)"

fclean : clean
	@printf "Cleaning target files...\n"
	@make -s fclean -C $(LIBDIR)/libft/
	@rm -f $(NAME)
	@printf "$(GREEN)Done\n$(NC)"

re : fclean all

.PHONY : all debug clean fclean re