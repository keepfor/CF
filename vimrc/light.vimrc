nnoremap <c-h> <c-w>h
nnoremap <c-j> <c-w>j
nnoremap <c-k> <c-w>k
nnoremap <c-l> <c-w>l
nnoremap <c-a> ggvG$
nnoremap <F5> :e input.txt
nnoremap <F6> :!make
nnoremap <F7> :q!
nnoremap <F8> :!make re
nnoremap <F4> :!bash /home/jackcai/scripts/start_ftu.sh
nnoremap <F3> :e ~/j/ftu_log_folder
nnoremap ; :

inoremap jk <esc>
inoremap kj <esc>
inoremap <Up> <c-p>
inoremap <c-i> <c-p>
inoremap <Down> <c-n>
inoremap <c-k> <c-n>

set visualbell
set t_ti= t_te= t_TI= t_TE=
set timeoutlen=10
set splitbelow
set expandtab
set nocompatible 
set number 
set nobackup
set backupcopy=yes 
set autochdir
set clipboard^=unnamed,unnamedplus 
set mouse=a
set smartindent autoindent cindent
set backspace=indent,eol,start
set shiftwidth=2 softtabstop=2 tabstop=2
set ignorecase smartcase 
set incsearch hlsearch 

command! -nargs=1 SS let @/ = '\V'.escape(<q-args>, '\')
