#include "../../include/cub3d.h"

static int	ft_pars_color(t_color *color, char *line)
{
	color->red = 0;
	line++;
	while ((*line > 9 && *line < 13) || *line == ' ')
		line++;
	while (*line && ft_isdigit(*line))
		color->red = color->red * 10 + *line++ - '0';
	if (*line == ',')
		line++;
	while (*line && ft_isdigit(*line))
		color->green = color->green * 10 + *line++ - '0';
	if (*line == ',')
		line++;
	while (*line && ft_isdigit(*line))
		color->blue = color->blue * 10 + *line++ - '0';
	while ((*line > 9 && *line < 13) || *line == ' ')
		line++;
	if (*line)
		return (-1);
	return (0);
}

static int	ft_pars_txtr(char **path, char *line)
{
	int i;
	int j;

	i = 1;
	if (*path)
		return (-1);
	if (line[1] == 'O' || line[1] == 'E' || line[1] == 'A')
		i = 2;
	while ((line[i] > 9 && line[i] < 13) || line[i] == ' ')
		i++;
	j = i;
	while (line[j] && ((line[j] < 9 || line[j] > 13) && line[j] != ' '))
		j++;
	if (!(*path = ft_substr(line, i, j)))
		return (-1);
	return (0);
}

static int	ft_pars_reso(t_cub *cub, char *line)
{
	line++;
	if (cub->reso.x != -1)
		return (-1);
	cub->reso.x = 0;
	cub->reso.y = 0;
	while ((*line > 9 && *line < 13) || *line == ' ')
		line++;
	while (*line && ft_isdigit(*line))
		cub->reso.x = cub->reso.x * 10 + *line++ - '0';
	while ((*line > 9 && *line < 13) || *line == ' ')
		line++;
	while (*line && ft_isdigit(*line))
		cub->reso.y = cub->reso.y * 10 + *line++ - '0';
	while ((*line > 9 && *line < 13) || *line == ' ')
		line++;
	if (*line)
		return (-1);
	return (0);
}

static int	ft_pars_affect(t_cub *cub, char *line)
{
	int	error_detector;

	if (*line == 'R')
		error_detector = ft_pars_reso(cub, line);
	else if (line[0] == 'N' && line[1] == 'O')
		error_detector = ft_pars_txtr(&(cub->n_txtr), line);
	else if (line[0] == 'S' && line[1] == 'O')
		error_detector = ft_pars_txtr(&(cub->s_txtr), line);
	else if (line[0] == 'W' && line[1] == 'E')
		error_detector = ft_pars_txtr(&(cub->w_txtr), line);
	else if (line[0] == 'E' && line[1] == 'A')
		error_detector = ft_pars_txtr(&(cub->e_txtr), line);
	else if (*line == 'S')
		error_detector = ft_pars_txtr(&(cub->spt_txtr), line);
	else if (*line == 'F')
		error_detector = ft_pars_color(&(cub->floor), line);
	else if (*line == 'C')
		error_detector = ft_pars_color(&(cub->ceiling), line);
	else
		error_detector = -1;
	return (error_detector);
}

void		ft_pars_file(t_cub *cub, char *file)
{
	int		fd;
	int		ret;
	char	*line;

	ft_pars_init(cub);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exit_error("Parsing: 'open' failed\n", NULL, NULL, 0);
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			ft_exit_error("Parsing: 'Get_Next_Line' failed\n", NULL, cub, fd);
		if (*line)
			if (ft_pars_affect(cub, line))
				ft_exit_error("Parsing: 'ft_pars_affect' failed\n", line, cub, fd);
		free(line);
		if (ft_is_parsing_finished(cub))
			break;
	}
	if (ft_is_parsing_ok(cub))
		ft_exit_error("Parsing: 'ft_is_parsing_ok' failed\n", NULL, cub, fd);
	ft_pars_map(cub, fd);
}
