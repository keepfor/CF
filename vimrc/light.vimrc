nnoremap <c-a> ggvG$

nnoremap <s-j> :e input.txt
nnoremap <s-k> :!make
nnoremap <s-l> :q!
nnoremap <s-r> :!make re

nnoremap <C-h> <C-w>h
nnoremap <C-j> <C-w>j
nnoremap <C-k> <C-w>k
nnoremap <C-l> <C-w>l

nnoremap <F4> :terminal bash /home/jackcai/scripts/start_ftu.sh
nnoremap <F3> :e ~/j/ftu_log_folder

inoremap jk <esc>
inoremap kj <esc>
nnoremap ; :

set visualbell
set t_ti= t_te=
set t_TI= t_TE=

set completeopt=longest,menu
set complete+=k

set timeoutlen=25

set splitbelow

if exists('$TMUX')
    let &t_SI = "\<Esc>Ptmux;\<Esc>\e[6 q\<Esc>\\"
    let &t_EI = "\<Esc>Ptmux;\<Esc>\e[2 q\<Esc>\\"
else
    let &t_SI = "\e[6 q"
    let &t_EI = "\e[2 q"
endif

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

set shiftwidth=2
set softtabstop=2
set tabstop=2
set backupcopy=yes 

set ignorecase smartcase 
set incsearch hlsearch 

filetype plugin indent on   
syntax on 
 
command! -nargs=1 SS let @/ = '\V'.escape(<q-args>, '\')
