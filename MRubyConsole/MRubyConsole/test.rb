class Test
  def initialize
    @name = "Alice"
    @age = 32

    @x = 0
    @y = 0

    puts "#{@name} is born."
  end

  def greeting
    puts @name
  end

  def get_position
    "x : #{@x} y : #{@y}"
  end

  def move_to( x, y )
    puts "#{@name} was Position #{self.get_position}"

    @x += x
    @y += y

    puts "#{@name} is Position #{self.get_position}"
  end

  def call_c_function
    CExtension.c_method
  end
end