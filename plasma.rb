require 'paint'
require 'io/console'
include Math

class Waves

  BLOCKS = "█▓▒░"
  EFFECTS = {
    gravy:     proc { |x,y,i| sin( (x/5.0) * cos((y/5.0)*(i)) ) },
    moire:     proc { |x,y,i| sin( tan( cos( x * y * (i/4) ) ) ) },
    sin:       proc { |x,y,i| (sin((i/2)/((sin(x*i)*(y*i)/200)+1))) },
    bars:      proc { |x,y,i| x /= 4.0; (((sin(y*(i/(cos(x))))*tan(x*i))*(i/(x+1)))*(i*(y+1))) },
    stripes:   proc { |x,y,i| ( sin( x * ( i / cos(y) ) ) * tan(y*i)) * (i/(x+1)) },
    elbow:     proc { |x,y,i| i / ( ( x*y/20 ) + 1) },
    # pulsing:   proc { |x,y,i| sin( (i/2) / ((sin(x*i) * cos(y*i) / 200) + 1) ) },
    blobs:     proc { |x,y,i| x /= 1.8; sin( sin(x*i) * cos(y*i) ) },
    neonfence: proc { |x,y,i| (sin(x * i) * tan(y * i)) * i },
  }

  attr_reader :width, :height

  def initialize(effect_name=nil)
    if effect_name 
      if @effect = EFFECTS[effect_name.to_sym]
        @effect_name = effect_name
      else
        puts "Unknown effect. Try one of these: #{EFFECTS.keys.join(", ")}"
        exit 1
      end
    else
      @effect_name,
      @effect  = EFFECTS.to_a.sample(1).first
    end      

    # @width, @height = 60, 40
    @height, 
    @width   = STDIN.winsize

    @height -= 2
    @width  -= 2

    @t       = 1
    @speed   = 5

  end

  def clear
    print "\e[2J"
  end

  def home
    print "\e[H"
  end

  def color(s, fore, back=nil)
    if back
      "\x1b[38;5;#{fore};48;5;#{back}m#{s}"
    else
      "\x1b[38;5;#{fore}m#{s}"
    end
  end

  def draw
    home
    puts "#{@effect_name}"
    i = @t / 1000.0
    height.times do |y|
      line = (0...width).map do |x| 
        val = @effect[x,y,i]
        val = [[0.0, val].max, 1.0].min
        val = (val * 255).to_i
        Paint[BLOCKS[0], [val, val, val]]
        # color(BLOCKS[0], val)
      end

      puts line.join('')
    end

    @t += @speed
  end

  def bench_draw
    i = @t / 1000.0
    height.times do |y|
      line = (0...width).map do |x| 
        val = @effect[x,y,i]
        val = [[0.0, val].max, 1.0].min
        val = (val * 255).to_i
      end
    end

    @t += @speed
  end

  def run
    clear

    loop do
      draw
      # sleep 0.01
    end
  rescue Interrupt
    puts "\e[0m"
  end

  def bench
    puts "benching #{@effect_name}"
    frames = 0
    last = Time.now.to_f
    loop do
      bench_draw
      frames += 1
      current = Time.now.to_f
      elapsed = current - last

      if elapsed > 1.0
        puts "fps: #{frames / elapsed}"
        last = current
        frames = 0
      end
    end
  end

end

Waves.new(ARGV.first).run
# Waves.new(ARGV.first).bench
