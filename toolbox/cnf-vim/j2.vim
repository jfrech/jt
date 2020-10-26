" j2 color scheme

" 160, 202, 208, 178

" http://vimdoc.sourceforge.net/htmldoc/syntax.html

set background=dark
let g:colors_name = "j2"

hi clear
if exists("syntax_on")
    syntax reset
endif

" TODO hi hs*

hi ColorColumn   cterm=bold ctermfg=none ctermbg=229
" hi Conceal
" hi Cursor
" hi lCursor
" hi CursorIm
hi CursorColumn cterm=none ctermfg=none ctermbg=none
hi CursorLine   cterm=none ctermfg=none ctermbg=none
" hi Directory
" hi DiffAdd
" hi DiffChange
" hi DiffDelete
" hi DiffText
hi EndOfBuffer    cterm=bold ctermfg=52 ctermbg=none
hi ErrorMsg       ctermfg=none ctermbg=196
" hi VertSplit
" hi Folded
" hi FoldColumn
" hi SignColumn
hi IncSearch      cterm=bold ctermfg=199 ctermbg=250
hi LineNr         ctermfg=244
" hi LineNrAbove
" hi LineNrBelow
hi CursorLineNr   cterm=none ctermfg=220 ctermbg=none
hi MatchParen     cterm=bold ctermfg=88 ctermbg=none
hi ModeMsg        cterm=italic ctermfg=124 ctermbg=none
hi MoreMsg        ctermfg=124
hi NonText        cterm=bold ctermfg=52 ctermbg=none
hi Normal         ctermfg=none
hi Pmenu          cterm=none ctermfg=none ctermbg=240
hi PmenuSel       cterm=bold ctermfg=202 ctermbg=238
" hi PmenuSbar
hi Question        cterm=bold ctermfg=82 ctermbg=none
hi QuestionFixLine cterm=bold ctermfg=82 ctermbg=none
hi Search          cterm=bold ctermfg=127 ctermbg=240
hi SpecialKey      cterm=bold ctermfg=52 ctermbg=none
" hi SpellBad
" hi SpellCap
" hi SpellLocal
" hi SpellRare
hi StatusLine       cterm=none ctermfg=220 ctermbg=236
hi StatusLineNC     cterm=none ctermfg=229 ctermbg=236
hi StatusLineTerm   cterm=none ctermfg=220 ctermbg=236
hi StatusLineTermNC cterm=none ctermfg=229 ctermbg=236
" hi TabLine
" hi TabLineFill
" hi TabLineSel
hi Terminal         cterm=none ctermfg=none ctermbg=none
hi Title            cterm=none ctermfg=220 ctermbg=none
hi Visual           cterm=bold ctermfg=none ctermbg=250
" hi VisualNOS
hi WarningMsg       cterm=bold ctermfg=196 ctermbg=255
" hi WildMenu
" hi Menu
" hi Scrollbar
" hi Tooltip



hi Comment        ctermfg=240

hi Constant       ctermfg=220
hi String         ctermfg=208
hi Character      ctermfg=220
hi Number         ctermfg=220
hi Boolean        ctermfg=220
hi Float          ctermfg=220

hi Identifier     ctermfg=244
hi Function       ctermfg=244

hi Statement      ctermfg=244
hi Conditional    ctermfg=244
hi Repeat         ctermfg=244
hi Label          ctermfg=160
hi Operator       ctermfg=160
hi Keyword        ctermfg=202
hi Exception      ctermfg=160

hi PreProc        ctermfg=184
hi Include        ctermfg=184
hi Define         ctermfg=184
hi Macro          ctermfg=184
hi PreCondit      ctermfg=184

hi Type           ctermfg=202
hi StorageClass   ctermfg=202
hi Structure      ctermfg=202
hi Typedef        ctermfg=202

hi Special        ctermfg=202
hi SpecialChar    ctermfg=202
hi Tag            ctermfg=202
hi Delimiter      ctermfg=202
hi SpecialComment cterm=bold ctermfg=202
hi Debug          ctermfg=82

hi Underlined     ctermfg=178  ctermbg=none cterm=underline

hi Ignore         ctermfg=52

hi Error          cterm=bold ctermfg=232 ctermbg=196

hi Todo           ctermfg=196 ctermbg=16 cterm=bold,italic
