class Tree

attr_accessor :topics

def initialize(topics)
  @topics = topics
end

def generate_tree(result)
  topic_tree = result[0].clone
  num_open = result[1]

  @topics.each do |i|

    next if i.nil?

    open_braces = (rand(100) == 1)
    close_braces = (rand(2) == 0)

    if (open_braces and @topics.length > 1)
      topic_tree += " #{i} ("
      @topics[@topics.index(i)] = nil
      num_open+=1
      result = generate_tree([topic_tree, num_open])
      topic_tree = result[0]
      num_open = result[1]
      next
    end
    # just add to string
    topic_tree += " #{i} "
    @topics[@topics.index(i)] = nil
    if (close_braces and num_open >= 1) || @topics.length == 0
      num_open-=1
      topic_tree += ")"
    end
  end

  return [topic_tree, num_open]
end

end

def get_word(lim)
  limit = rand(1..lim)
  (('a'..'z').to_a + ('A'..'Z').to_a).shuffle[0,limit].join
end

def get_question(lim, w_lim)
  str = ""
  range = 1..rand(1..w_lim)
  (range).each {|t|
    str += ( " " + get_word(lim))
  }
  return str
end

# 100000
topic_count = 200000
topics = Array.new
topics_cpy = Array.new

t_limit = 100000
q_limit = 100000
k_limit = 100000

topic_count.times {|i|
  topic = get_word(10)
  topics_cpy.push(topic.dup)
  topics.push(topic)
}

topics.uniq!
topics = topics[0...(t_limit-1)]
topics.select!{|t| t.length > 0}

topics_cpy.uniq!
topics_cpy = topics_cpy[0...(t_limit-1)]
topics_cpy.select!{|t| t.length > 0}

# Initialize
tree = Tree.new(topics_cpy)

result = tree.generate_tree(["ANI (", 0])
topic_tree = result[0]
num_open = result[1] + 1

topic_tree+= " "

(0...num_open).each{|i|
  topic_tree+=") "
}

topics.push("ANI")
questions = []

puts topics.length
puts topic_tree
puts q_limit

control_queries = []

t_limit.times do |q|
  query = get_question(10,20)
  topic = topics[rand(t_limit)]
  questions.push("#{topic}: #{query}?")
  control_queries.push("#{topic} #{query}")
end

puts questions

puts k_limit + control_queries.length

queries = []

k_limit.times do |t|
  queries.push("#{topics[rand(t_limit)]} #{get_question(10,2)}") 
end

puts control_queries + queries
