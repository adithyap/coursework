#include "options.hpp"

bool Options::_ohhh;
bool Options::_page_table;
bool Options::_frame_table;
bool Options::_summary;

bool Options::_dbg_page_table;
bool Options::_dbg_frame_table;
bool Options::_dbg_aging;

void Options::init_options(char *options)
{
    _ohhh = false;
    _page_table = false;
    _frame_table = false;
    _summary = false;

    _dbg_aging = false;
    _dbg_page_table = false;
    _dbg_frame_table = false;

    if (options == NULL)
    {
        printf("Options::parse_options - input string is NULL");
        return;
    }

    int len = strlen(options);

    for ( int i = 0; i < len; i++ )
    {
        switch(options[i])
        {
            case 'o':
            case 'O':
                _ohhh = true;
                break;

            case 'p':
                _dbg_page_table = true;
                break;

            case 'P':
                _page_table = true;
                break;

            case 'f':
                _dbg_frame_table = true;
                break;

            case 'F':
                _frame_table = true;
                break;

            case 's':
            case 'S':
                _summary = true;
                break;

            case 'a':
            case 'A':
                _dbg_aging = true;
                break;

            default:
                printf("Options::init_options - Unknown argument %c, will ignore\n", options[i]);
                break;
        }
    }
}

bool Options::ohhh()
{
    return _ohhh;
}

bool Options::page_table()
{
    return _page_table;
}

bool Options::frame_table()
{
    return _frame_table;
}

bool Options::summary()
{
    return _summary;
}

bool Options::dbg_page_table()
{
    return _dbg_page_table;
}

bool Options::dbg_frame_table()
{
    return _dbg_frame_table;
}

bool Options::dbg_aging()
{
    return _dbg_aging;
}
