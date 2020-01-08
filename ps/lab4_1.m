disp("Running");

function out=read_file_words(file_path)
  file = fopen(file_path, 'r');
  words_list = textscan(file, "%s");
  out = words_list{1};
  fclose(file);
endfunction

function out=is_email_spam(file_path)
  spam_words = read_file_words('keywords_spam.txt');
  ham_words = read_file_words('keywords_ham.txt');
  email_words = read_file_words(file_path);
  all_words = unique([spam_words; ham_words]);
  
  spam_words_length = numel(spam_words);
  ham_words_length = numel(ham_words);
  email_words_length = numel(email_words);
  all_words_length = numel(all_words);
  
  probspam = spam_words_length / all_words_length;
  probham = ham_words_length / all_words_length;
  
  for i = 1:all_words_length
    if ismember(all_words(i), email_words)
      probspam = probspam * sum(strcmp(all_words(i), spam_words)) / spam_words_length;
      probham = probham * sum(strcmp(all_words(i), ham_words)) / ham_words_length;
    else
      probspam = probspam * (1 - sum(strcmp(all_words(i), spam_words) / spam_words_length));
      probham = probham * (1 - sum(strcmp(all_words(i), ham_words) / ham_words_length));
    endif
  endfor
  
  out = probspam > probham;
endfunction
