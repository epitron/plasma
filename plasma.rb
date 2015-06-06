require 'paint'
include Math

class Waves

  BLOCKS = "█▓▒░"

  attr_reader :width, :height

  def initialize
    @width, @height = 60, 40
    @t = 1
  end

  def clear
    puts "\e[2J"
  end

  def home
    puts "\e[H"
  end

  def draw
    i = @t / 1000.0
    height.times do |y|
      line = (0...width).map do |x| 
        # val = (sin(x * i) * tan(y * i)) * i
        val = sin( tan( cos( x * y * (i/4) ) ) )
        val = [[0.0, val].max, 1.0].min
        val = (val * 255).to_i
        Paint[BLOCKS[0], [val, val, val]]
      end

      puts line.join('')
    end

    @t += 1
  end

  def run
    clear

    loop do
      home
      draw
#      sleep 0.01
    end
  end

end

Waves.new.run
