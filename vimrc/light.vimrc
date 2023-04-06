nnoremap <s-j> :e input.txt
nnoremap <s-k> :!make
nnoremap <s-l> :q!
nnoremap <s-r> :!make re

inoremap { {}<left>
inoremap <expr> <CR> search('{\%#}', 'n') ? "\<CR>\<CR>\<Up>\<C-f>" : "\<CR>"
inoremap <expr> } strpart(getline('.'), col('.')-1, 1) == "}" ? "\<Right>" : "}"

inoremap ( ()<Left>
inoremap <expr> ) strpart(getline('.'), col('.')-1, 1) == ")" ? "\<Right>" : ")"

inoremap <expr> ' strpart(getline('.'), col('.')-1, 1) == "\'" ? "\<Right>" : "\'\'\<Left>"

set visualbell

set t_ti= t_te=
set t_TI= t_TE=

set completeopt=longest,menu,menuone
set complete+=k

nnoremap <F4> :! . ~/j/start_ftu.sh
nnoremap <F3> :e ~/j/ftu_log_folder

command! -nargs=1 SS let @/ = '\V'.escape(<q-args>, '\')

set timeoutlen=25

set splitbelow

if exists('$TMUX')
    let &t_SI = "\<Esc>Ptmux;\<Esc>\e[6 q\<Esc>\\"
    let &t_EI = "\<Esc>Ptmux;\<Esc>\e[2 q\<Esc>\\"
else
    let &t_SI = "\e[6 q"
    let &t_EI = "\e[2 q"
endif

inoremap jk <esc>
inoremap kj <esc>
nnoremap ; :

set expandtab
set nocompatible 
set number 
set nobackup
set autochdir

set clipboard^=unnamed,unnamedplus 
set mouse=a

set smartindent 
set autoindent
set cindent
set backspace=indent,eol,start

filetype plugin indent on   
syntax on 
 
set shiftwidth=2
set softtabstop=2
set tabstop=2

set backupcopy=yes 

set ignorecase smartcase 
set incsearch hlsearch 

nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l
