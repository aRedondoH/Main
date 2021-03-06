(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(custom-safe-themes
   (quote
    ("05c3bc4eb1219953a4f182e10de1f7466d28987f48d647c01f1f0037ff35ab9a" "b06aaf5cefc4043ba018ca497a9414141341cb5a2152db84a9a80020d35644d1" default)))
 '(inhibit-startup-screen t)
 '(package-selected-packages
   (quote
    (csv-mode anaconda-mode elpy autopair auctex font-utils monokai-theme))))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )

(require 'package) ;; You might already have this line
(add-to-list 'package-archives
             '("melpa" . "http://melpa.org/packages/"))
(when (< emacs-major-version 24)
  ;; For important compatibility libraries like cl-lib
  (add-to-list 'package-archives '("gnu" . "http://elpa.gnu.org/packages/")))
(package-initialize) ;; 
(load-theme 'monokai t)

;; Allow hash to be entered  
(global-set-key (kbd "M-3") '(lambda () (interactive) (insert "#"))) 

;; Allow at to be entered
(global-set-key (kbd "M-2") '(lambda () (interactive) (insert "@")))


(global-set-key (kbd "M-1") "|")
(global-set-key (kbd "M-2") "@")
(global-set-key (kbd "M-3") "#")
;; (global-set-key (kbd "M-º") "\\")
;; (global-set-key (kbd "M-ç") "}")
(global-set-key (kbd "M-+") "]")
;; (global-set-key (kbd "M-ñ") "~")

;; Save sessions
(desktop-save-mode 1)

;; latex
(setq TeX-auto-save t)
(setq TeX-parse-self t)
(setq TeX-save-query nil)
					;(setq TeX-PDF-mode t)

(require 'flymake)

(defun flymake-get-tex-args (file-name)
(list "pdflatex"
(list "-file-line-error" "-draftmode" "-interaction=nonstopmode" file-name)))

(add-hook 'LaTeX-mode-hook 'flymake-mode)

(setq ispell-program-name "aspell") ; could be ispell as well, depending on your preferences
(setq ispell-dictionary "english") ; this can obviously be set to any language your spell-checking program supports

(add-hook 'LaTeX-mode-hook 'flyspell-mode)
(add-hook 'LaTeX-mode-hook 'flyspell-buffer)

;;(defun my-make-slash-backslash ()
;;  (local-set-key (kbd "/") "\\"))

(add-hook 'TeX-mode-hook 'my-make-slash-backslash)

(defun kill-other-buffers ()
  "Kill all other buffers."
  (interactive)
  (mapc 'kill-buffer (delq (current-buffer) (buffer-list))))

;; this should be defined as default :-)
(setq mac-right-option-modifier nil)

