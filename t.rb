#alpha = "a b c d e f g h i j k l m n o p q r s t u v w x y z"
alpha = "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z a b c d e f g h i j k l m n o p q r s t u v w x y z"
alpha = alpha.split(" ")

alpha.each_with_index { |k,v|
   puts "    case '#{k}' :
      alpha_check(#{v},\"#{k}\");
      return alphabet[#{v}];"
  }
