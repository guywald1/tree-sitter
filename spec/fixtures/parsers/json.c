#include "tree_sitter/parser.h"

#define STATE_COUNT 69
#define SYMBOL_COUNT 19

enum {
    sym_value = ts_builtin_sym_start,
    sym_object,
    sym_array,
    sym_string,
    sym_number,
    sym_null,
    sym_true,
    sym_false,
    aux_sym_object_repeat1,
    aux_sym_array_repeat1,
    aux_sym_STR_LBRACE,
    aux_sym_STR_COLON,
    aux_sym_STR_COMMA,
    aux_sym_STR_RBRACE,
    aux_sym_STR_LBRACK,
    aux_sym_STR_RBRACK,
};

static const char *ts_symbol_names[] = {
    [ts_builtin_sym_document] = "DOCUMENT",
    [sym_value] = "value",
    [sym_object] = "object",
    [sym_array] = "array",
    [ts_builtin_sym_error] = "ERROR",
    [ts_builtin_sym_end] = "END",
    [sym_string] = "string",
    [sym_number] = "number",
    [sym_null] = "null",
    [sym_true] = "true",
    [sym_false] = "false",
    [aux_sym_object_repeat1] = "object_repeat1",
    [aux_sym_array_repeat1] = "array_repeat1",
    [aux_sym_STR_LBRACE] = "STR_{",
    [aux_sym_STR_COLON] = "STR_:",
    [aux_sym_STR_COMMA] = "STR_,",
    [aux_sym_STR_RBRACE] = "STR_}",
    [aux_sym_STR_LBRACK] = "STR_[",
    [aux_sym_STR_RBRACK] = "STR_]",
};

static const int ts_hidden_symbol_flags[SYMBOL_COUNT] = {
    [aux_sym_object_repeat1] = 1,
    [aux_sym_array_repeat1] = 1,
    [aux_sym_STR_LBRACE] = 1,
    [aux_sym_STR_COLON] = 1,
    [aux_sym_STR_COMMA] = 1,
    [aux_sym_STR_RBRACE] = 1,
    [aux_sym_STR_LBRACK] = 1,
    [aux_sym_STR_RBRACK] = 1,
};

static TSTree *ts_lex(TSLexer *lexer, TSStateId lex_state) {
    START_LEXER();
    switch (lex_state) {
        case 1:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(1);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            LEX_ERROR();
        case 2:
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            LEX_ERROR();
        case 3:
            ACCEPT_TOKEN(sym_string);
        case 4:
            if (lookahead == '\"')
                ADVANCE(5);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            LEX_ERROR();
        case 5:
            if (lookahead == '\"')
                ADVANCE(3);
            if (lookahead == '\\')
                ADVANCE(4);
            if (!((lookahead == 0) ||
                (lookahead == '\"') ||
                (lookahead == '\\')))
                ADVANCE(2);
            ACCEPT_TOKEN(sym_string);
        case 6:
            if (lookahead == '.')
                ADVANCE(7);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            ACCEPT_TOKEN(sym_number);
        case 7:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            LEX_ERROR();
        case 8:
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(8);
            ACCEPT_TOKEN(sym_number);
        case 9:
            ACCEPT_TOKEN(aux_sym_STR_LBRACK);
        case 10:
            if (lookahead == 'a')
                ADVANCE(11);
            LEX_ERROR();
        case 11:
            if (lookahead == 'l')
                ADVANCE(12);
            LEX_ERROR();
        case 12:
            if (lookahead == 's')
                ADVANCE(13);
            LEX_ERROR();
        case 13:
            if (lookahead == 'e')
                ADVANCE(14);
            LEX_ERROR();
        case 14:
            ACCEPT_TOKEN(sym_false);
        case 15:
            if (lookahead == 'u')
                ADVANCE(16);
            LEX_ERROR();
        case 16:
            if (lookahead == 'l')
                ADVANCE(17);
            LEX_ERROR();
        case 17:
            if (lookahead == 'l')
                ADVANCE(18);
            LEX_ERROR();
        case 18:
            ACCEPT_TOKEN(sym_null);
        case 19:
            if (lookahead == 'r')
                ADVANCE(20);
            LEX_ERROR();
        case 20:
            if (lookahead == 'u')
                ADVANCE(21);
            LEX_ERROR();
        case 21:
            if (lookahead == 'e')
                ADVANCE(22);
            LEX_ERROR();
        case 22:
            ACCEPT_TOKEN(sym_true);
        case 23:
            ACCEPT_TOKEN(aux_sym_STR_LBRACE);
        case 24:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(24);
            LEX_ERROR();
        case 25:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 26:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(26);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 27:
            ACCEPT_TOKEN(aux_sym_STR_RBRACE);
        case 28:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(28);
            if (lookahead == '\"')
                ADVANCE(2);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            LEX_ERROR();
        case 29:
            ACCEPT_TOKEN(aux_sym_STR_RBRACK);
        case 30:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(30);
            if (lookahead == ',')
                ADVANCE(31);
            if (lookahead == ']')
                ADVANCE(29);
            LEX_ERROR();
        case 31:
            ACCEPT_TOKEN(aux_sym_STR_COMMA);
        case 32:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(32);
            if (lookahead == ']')
                ADVANCE(29);
            LEX_ERROR();
        case 33:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(33);
            if (lookahead == ',')
                ADVANCE(31);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 34:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(34);
            if (lookahead == ':')
                ADVANCE(35);
            LEX_ERROR();
        case 35:
            ACCEPT_TOKEN(aux_sym_STR_COLON);
        case 36:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(36);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case 37:
            START_TOKEN();
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(37);
            if (lookahead == '\"')
                ADVANCE(2);
            LEX_ERROR();
        case 38:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(31);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(35);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        case ts_lex_state_error:
            START_TOKEN();
            if (lookahead == 0)
                ADVANCE(25);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                ADVANCE(38);
            if (lookahead == '\"')
                ADVANCE(2);
            if (lookahead == ',')
                ADVANCE(31);
            if ('0' <= lookahead && lookahead <= '9')
                ADVANCE(6);
            if (lookahead == ':')
                ADVANCE(35);
            if (lookahead == '[')
                ADVANCE(9);
            if (lookahead == ']')
                ADVANCE(29);
            if (lookahead == 'f')
                ADVANCE(10);
            if (lookahead == 'n')
                ADVANCE(15);
            if (lookahead == 't')
                ADVANCE(19);
            if (lookahead == '{')
                ADVANCE(23);
            if (lookahead == '}')
                ADVANCE(27);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 1,
    [1] = 24,
    [2] = 24,
    [3] = 26,
    [4] = 28,
    [5] = 30,
    [6] = 30,
    [7] = 26,
    [8] = 28,
    [9] = 24,
    [10] = 30,
    [11] = 30,
    [12] = 32,
    [13] = 1,
    [14] = 30,
    [15] = 30,
    [16] = 32,
    [17] = 30,
    [18] = 33,
    [19] = 34,
    [20] = 30,
    [21] = 1,
    [22] = 33,
    [23] = 33,
    [24] = 26,
    [25] = 28,
    [26] = 30,
    [27] = 33,
    [28] = 32,
    [29] = 33,
    [30] = 33,
    [31] = 33,
    [32] = 34,
    [33] = 33,
    [34] = 1,
    [35] = 33,
    [36] = 36,
    [37] = 37,
    [38] = 33,
    [39] = 33,
    [40] = 34,
    [41] = 1,
    [42] = 33,
    [43] = 36,
    [44] = 36,
    [45] = 33,
    [46] = 36,
    [47] = 33,
    [48] = 33,
    [49] = 36,
    [50] = 30,
    [51] = 30,
    [52] = 36,
    [53] = 30,
    [54] = 30,
    [55] = 32,
    [56] = 24,
    [57] = 24,
    [58] = 33,
    [59] = 34,
    [60] = 24,
    [61] = 1,
    [62] = 33,
    [63] = 36,
    [64] = 24,
    [65] = 24,
    [66] = 36,
    [67] = 24,
    [68] = 24,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static const TSParseAction ts_parse_actions[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [sym_value] = SHIFT(1),
        [sym_object] = SHIFT(2),
        [sym_array] = SHIFT(2),
        [sym_string] = SHIFT(2),
        [sym_number] = SHIFT(2),
        [sym_null] = SHIFT(2),
        [sym_true] = SHIFT(2),
        [sym_false] = SHIFT(2),
        [aux_sym_STR_LBRACE] = SHIFT(3),
        [aux_sym_STR_LBRACK] = SHIFT(4),
    },
    [1] = {
        [ts_builtin_sym_end] = ACCEPT_INPUT(),
    },
    [2] = {
        [ts_builtin_sym_end] = REDUCE(sym_value, 1),
    },
    [3] = {
        [ts_builtin_sym_error] = SHIFT(58),
        [sym_string] = SHIFT(59),
        [aux_sym_STR_RBRACE] = SHIFT(60),
    },
    [4] = {
        [sym_value] = SHIFT(5),
        [sym_object] = SHIFT(6),
        [sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(5),
        [sym_string] = SHIFT(6),
        [sym_number] = SHIFT(6),
        [sym_null] = SHIFT(6),
        [sym_true] = SHIFT(6),
        [sym_false] = SHIFT(6),
        [aux_sym_STR_LBRACE] = SHIFT(7),
        [aux_sym_STR_LBRACK] = SHIFT(8),
        [aux_sym_STR_RBRACK] = SHIFT(9),
    },
    [5] = {
        [aux_sym_array_repeat1] = SHIFT(55),
        [aux_sym_STR_COMMA] = SHIFT(13),
        [aux_sym_STR_RBRACK] = SHIFT(56),
    },
    [6] = {
        [aux_sym_array_repeat1] = REDUCE(sym_value, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_value, 1),
        [aux_sym_STR_RBRACK] = REDUCE(sym_value, 1),
    },
    [7] = {
        [ts_builtin_sym_error] = SHIFT(18),
        [sym_string] = SHIFT(19),
        [aux_sym_STR_RBRACE] = SHIFT(20),
    },
    [8] = {
        [sym_value] = SHIFT(10),
        [sym_object] = SHIFT(6),
        [sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(10),
        [sym_string] = SHIFT(6),
        [sym_number] = SHIFT(6),
        [sym_null] = SHIFT(6),
        [sym_true] = SHIFT(6),
        [sym_false] = SHIFT(6),
        [aux_sym_STR_LBRACE] = SHIFT(7),
        [aux_sym_STR_LBRACK] = SHIFT(8),
        [aux_sym_STR_RBRACK] = SHIFT(11),
    },
    [9] = {
        [ts_builtin_sym_end] = REDUCE(sym_array, 2),
    },
    [10] = {
        [aux_sym_array_repeat1] = SHIFT(12),
        [aux_sym_STR_COMMA] = SHIFT(13),
        [aux_sym_STR_RBRACK] = SHIFT(14),
    },
    [11] = {
        [aux_sym_array_repeat1] = REDUCE(sym_array, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_array, 2),
        [aux_sym_STR_RBRACK] = REDUCE(sym_array, 2),
    },
    [12] = {
        [aux_sym_STR_RBRACK] = SHIFT(17),
    },
    [13] = {
        [sym_value] = SHIFT(15),
        [sym_object] = SHIFT(6),
        [sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(15),
        [sym_string] = SHIFT(6),
        [sym_number] = SHIFT(6),
        [sym_null] = SHIFT(6),
        [sym_true] = SHIFT(6),
        [sym_false] = SHIFT(6),
        [aux_sym_STR_LBRACE] = SHIFT(7),
        [aux_sym_STR_LBRACK] = SHIFT(8),
    },
    [14] = {
        [aux_sym_array_repeat1] = REDUCE(sym_array, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_array, 3),
        [aux_sym_STR_RBRACK] = REDUCE(sym_array, 3),
    },
    [15] = {
        [aux_sym_array_repeat1] = SHIFT(16),
        [aux_sym_STR_COMMA] = SHIFT(13),
        [aux_sym_STR_RBRACK] = REDUCE(aux_sym_array_repeat1, 2),
    },
    [16] = {
        [aux_sym_STR_RBRACK] = REDUCE(aux_sym_array_repeat1, 3),
    },
    [17] = {
        [aux_sym_array_repeat1] = REDUCE(sym_array, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_array, 4),
        [aux_sym_STR_RBRACK] = REDUCE(sym_array, 4),
    },
    [18] = {
        [aux_sym_object_repeat1] = SHIFT(52),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = SHIFT(53),
    },
    [19] = {
        [aux_sym_STR_COLON] = SHIFT(21),
    },
    [20] = {
        [aux_sym_array_repeat1] = REDUCE(sym_object, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 2),
        [aux_sym_STR_RBRACK] = REDUCE(sym_object, 2),
    },
    [21] = {
        [sym_value] = SHIFT(22),
        [sym_object] = SHIFT(23),
        [sym_array] = SHIFT(23),
        [sym_string] = SHIFT(23),
        [sym_number] = SHIFT(23),
        [sym_null] = SHIFT(23),
        [sym_true] = SHIFT(23),
        [sym_false] = SHIFT(23),
        [aux_sym_STR_LBRACE] = SHIFT(24),
        [aux_sym_STR_LBRACK] = SHIFT(25),
    },
    [22] = {
        [aux_sym_object_repeat1] = SHIFT(49),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = SHIFT(50),
    },
    [23] = {
        [aux_sym_object_repeat1] = REDUCE(sym_value, 1),
        [aux_sym_STR_COMMA] = REDUCE(sym_value, 1),
        [aux_sym_STR_RBRACE] = REDUCE(sym_value, 1),
    },
    [24] = {
        [ts_builtin_sym_error] = SHIFT(31),
        [sym_string] = SHIFT(32),
        [aux_sym_STR_RBRACE] = SHIFT(33),
    },
    [25] = {
        [sym_value] = SHIFT(26),
        [sym_object] = SHIFT(6),
        [sym_array] = SHIFT(6),
        [ts_builtin_sym_error] = SHIFT(26),
        [sym_string] = SHIFT(6),
        [sym_number] = SHIFT(6),
        [sym_null] = SHIFT(6),
        [sym_true] = SHIFT(6),
        [sym_false] = SHIFT(6),
        [aux_sym_STR_LBRACE] = SHIFT(7),
        [aux_sym_STR_LBRACK] = SHIFT(8),
        [aux_sym_STR_RBRACK] = SHIFT(27),
    },
    [26] = {
        [aux_sym_array_repeat1] = SHIFT(28),
        [aux_sym_STR_COMMA] = SHIFT(13),
        [aux_sym_STR_RBRACK] = SHIFT(29),
    },
    [27] = {
        [aux_sym_object_repeat1] = REDUCE(sym_array, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_array, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_array, 2),
    },
    [28] = {
        [aux_sym_STR_RBRACK] = SHIFT(30),
    },
    [29] = {
        [aux_sym_object_repeat1] = REDUCE(sym_array, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_array, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_array, 3),
    },
    [30] = {
        [aux_sym_object_repeat1] = REDUCE(sym_array, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_array, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_array, 4),
    },
    [31] = {
        [aux_sym_object_repeat1] = SHIFT(46),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = SHIFT(47),
    },
    [32] = {
        [aux_sym_STR_COLON] = SHIFT(34),
    },
    [33] = {
        [aux_sym_object_repeat1] = REDUCE(sym_object, 2),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 2),
        [aux_sym_STR_RBRACE] = REDUCE(sym_object, 2),
    },
    [34] = {
        [sym_value] = SHIFT(35),
        [sym_object] = SHIFT(23),
        [sym_array] = SHIFT(23),
        [sym_string] = SHIFT(23),
        [sym_number] = SHIFT(23),
        [sym_null] = SHIFT(23),
        [sym_true] = SHIFT(23),
        [sym_false] = SHIFT(23),
        [aux_sym_STR_LBRACE] = SHIFT(24),
        [aux_sym_STR_LBRACK] = SHIFT(25),
    },
    [35] = {
        [aux_sym_object_repeat1] = SHIFT(36),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = SHIFT(38),
    },
    [36] = {
        [aux_sym_STR_RBRACE] = SHIFT(45),
    },
    [37] = {
        [ts_builtin_sym_error] = SHIFT(39),
        [sym_string] = SHIFT(40),
    },
    [38] = {
        [aux_sym_object_repeat1] = REDUCE(sym_object, 5),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 5),
        [aux_sym_STR_RBRACE] = REDUCE(sym_object, 5),
    },
    [39] = {
        [aux_sym_object_repeat1] = SHIFT(44),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_object_repeat1, 2),
    },
    [40] = {
        [aux_sym_STR_COLON] = SHIFT(41),
    },
    [41] = {
        [sym_value] = SHIFT(42),
        [sym_object] = SHIFT(23),
        [sym_array] = SHIFT(23),
        [sym_string] = SHIFT(23),
        [sym_number] = SHIFT(23),
        [sym_null] = SHIFT(23),
        [sym_true] = SHIFT(23),
        [sym_false] = SHIFT(23),
        [aux_sym_STR_LBRACE] = SHIFT(24),
        [aux_sym_STR_LBRACK] = SHIFT(25),
    },
    [42] = {
        [aux_sym_object_repeat1] = SHIFT(43),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_object_repeat1, 4),
    },
    [43] = {
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_object_repeat1, 5),
    },
    [44] = {
        [aux_sym_STR_RBRACE] = REDUCE(aux_sym_object_repeat1, 3),
    },
    [45] = {
        [aux_sym_object_repeat1] = REDUCE(sym_object, 6),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 6),
        [aux_sym_STR_RBRACE] = REDUCE(sym_object, 6),
    },
    [46] = {
        [aux_sym_STR_RBRACE] = SHIFT(48),
    },
    [47] = {
        [aux_sym_object_repeat1] = REDUCE(sym_object, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 3),
        [aux_sym_STR_RBRACE] = REDUCE(sym_object, 3),
    },
    [48] = {
        [aux_sym_object_repeat1] = REDUCE(sym_object, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 4),
        [aux_sym_STR_RBRACE] = REDUCE(sym_object, 4),
    },
    [49] = {
        [aux_sym_STR_RBRACE] = SHIFT(51),
    },
    [50] = {
        [aux_sym_array_repeat1] = REDUCE(sym_object, 5),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 5),
        [aux_sym_STR_RBRACK] = REDUCE(sym_object, 5),
    },
    [51] = {
        [aux_sym_array_repeat1] = REDUCE(sym_object, 6),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 6),
        [aux_sym_STR_RBRACK] = REDUCE(sym_object, 6),
    },
    [52] = {
        [aux_sym_STR_RBRACE] = SHIFT(54),
    },
    [53] = {
        [aux_sym_array_repeat1] = REDUCE(sym_object, 3),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 3),
        [aux_sym_STR_RBRACK] = REDUCE(sym_object, 3),
    },
    [54] = {
        [aux_sym_array_repeat1] = REDUCE(sym_object, 4),
        [aux_sym_STR_COMMA] = REDUCE(sym_object, 4),
        [aux_sym_STR_RBRACK] = REDUCE(sym_object, 4),
    },
    [55] = {
        [aux_sym_STR_RBRACK] = SHIFT(57),
    },
    [56] = {
        [ts_builtin_sym_end] = REDUCE(sym_array, 3),
    },
    [57] = {
        [ts_builtin_sym_end] = REDUCE(sym_array, 4),
    },
    [58] = {
        [aux_sym_object_repeat1] = SHIFT(66),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = SHIFT(67),
    },
    [59] = {
        [aux_sym_STR_COLON] = SHIFT(61),
    },
    [60] = {
        [ts_builtin_sym_end] = REDUCE(sym_object, 2),
    },
    [61] = {
        [sym_value] = SHIFT(62),
        [sym_object] = SHIFT(23),
        [sym_array] = SHIFT(23),
        [sym_string] = SHIFT(23),
        [sym_number] = SHIFT(23),
        [sym_null] = SHIFT(23),
        [sym_true] = SHIFT(23),
        [sym_false] = SHIFT(23),
        [aux_sym_STR_LBRACE] = SHIFT(24),
        [aux_sym_STR_LBRACK] = SHIFT(25),
    },
    [62] = {
        [aux_sym_object_repeat1] = SHIFT(63),
        [aux_sym_STR_COMMA] = SHIFT(37),
        [aux_sym_STR_RBRACE] = SHIFT(64),
    },
    [63] = {
        [aux_sym_STR_RBRACE] = SHIFT(65),
    },
    [64] = {
        [ts_builtin_sym_end] = REDUCE(sym_object, 5),
    },
    [65] = {
        [ts_builtin_sym_end] = REDUCE(sym_object, 6),
    },
    [66] = {
        [aux_sym_STR_RBRACE] = SHIFT(68),
    },
    [67] = {
        [ts_builtin_sym_end] = REDUCE(sym_object, 3),
    },
    [68] = {
        [ts_builtin_sym_end] = REDUCE(sym_object, 4),
    },
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_json);