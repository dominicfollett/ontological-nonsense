def generate_tree(result)
  topic_tree = result[0]
  topics = result[1]
  num_open = result[2]

  topics.each do |i|

    open_braces = (rand(2) == 0)
    close_braces = (rand(2) == 0)

    if (open_braces and topics.length > 1)
      topic_tree += " #{i} ("
      topics.slice!(0)
      num_open+=1
      result = generate_tree([topic_tree, topics, num_open])
      topics = result[1]
      puts "----"
      puts topics
      puts "----"
      topic_tree = result[0]
      num_open = result[2]
      next
    end
    # just add to string
    topic_tree += " #{i} "
    topics.slice!(0)
    if (close_braces and num_open >= 1) || topics.length == 0
      num_open-=1
      topic_tree += ")"
    end
  end

  return [topic_tree, topics, num_open]
end


# 100000
topic_count = 10
topics = []

topic_count.times {|i|
  limit = rand(5)
  topic = ('A'..'Z').to_a.shuffle[0,limit].join
  topics.push(topic)
}

topics.uniq!
topics = topics[0...4]

topics.select!{|t| t.length > 0}

#result = generate_tree(["", topics], false)
result = generate_tree(["ANI (", topics, 0])
topic_tree = result[0]
num_open = result[2] + 1

topic_tree+= " "

(0...num_open).each{|i|
  topic_tree+=") "
}

puts topic_tree
