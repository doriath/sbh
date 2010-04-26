require 'rake/clean'

def time
  start = Time.now
  yield
  Time.now - start
end

CLEAN.include('bin/*')
TARGETS = %w{bin/sbh_general bin/sbh_general_no_trunc bin/sbh_positive bin/sbh_negative bin/sbh_check bin/sbh_print_graph}
SRC = FileList['src/*.cpp']

FileList['src/*.cpp'].each do |src_file|
  obj_file = File.join("bin", File.basename(src_file).ext('o'))
  file obj_file => [src_file] do
    sh "g++ -c -o #{obj_file} #{src_file}"
  end
end

TARGETS.each do |target|
  src_file = File.join('src', File.basename(target).ext('cpp'))
  file target => ['bin/sbh_lib.o', 'bin/graph.o', src_file] do |t|
    sh "g++ -o #{t.name} #{src_file} bin/sbh_lib.o bin/graph.o"
  end
end


task :default => :compile

desc "Compile all source files"
task :compile => TARGETS 

desc "Generate report"
task :report => "doc/report.tex" do
  2.times do 
    break unless system('cd doc; pdflatex -halt-on-error report.tex') 
  end
end

desc "Run sbh positive for all input files"
task :positive => "bin/sbh_positive" do
  instances_dir = "instances/positive/"
  printf("%-10s | %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| \n", "File", "Words", "N", "Length", "Used w", "Made w", "Repeats", "Error", "Time")
  print "------------------------------------------------------------------------------------\n";

  Dir.foreach(instances_dir) do |file|
    instance_path = File.join(instances_dir, file);
    next unless File.file?(instance_path)

	elapsed = time {
    `bin/sbh_positive #{instance_path} > out`
	}

    result = `bin/sbh_check #{instance_path} out`

    n = file[/\.(\d+)/, 1].to_i
	given_n = n + file[/\+(\d+)/, 1].to_i
	res = result.split(" ")
    printf("%-10s | %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7f|\n", file, given_n, n, res[0], res[1], res[2], res[3], n - res[1].to_i, elapsed)
  end
  File.delete("out")
end

desc "Run sbh general for all positive input files"
task :general_positive => "bin/sbh_general" do
  instances_dir = "instances/positive/"
  printf("%-10s | %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| \n", "File", "Words", "N", "Length", "Used w", "Made w", "Repeats", "Error", "Time")
  print "------------------------------------------------------------------------------------\n";

  Dir.foreach(instances_dir) do |file|
    instance_path = File.join(instances_dir, file);
    next unless File.file?(instance_path)

	elapsed = time {
    `bin/sbh_general #{instance_path} > out`
	}
	
    result = `bin/sbh_check #{instance_path} out`
    
    n = file[/\.(\d+)/, 1].to_i
	given_n = n + file[/\+(\d+)/, 1].to_i
	res = result.split(" ")
    printf("%-10s | %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7f|\n", file, given_n, n, res[0], res[1], res[2], res[3], n - res[1].to_i, elapsed)
  end
  File.delete("out")
end

desc "Run sbh general for all negative input files"
task :general_negative => "bin/sbh_general" do
  instances_dir = "instances/negative/"
  printf("%-10s | %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| \n", "File", "Words", "N", "Length", "Used w", "Made w", "Repeats", "Error", "Time")
  print "------------------------------------------------------------------------------------\n";

  Dir.foreach(instances_dir) do |file|
    instance_path = File.join(instances_dir, file);
    next unless File.file?(instance_path)

	elapsed = time {
    `bin/sbh_general #{instance_path} > out`
	}
	
    result = `bin/sbh_check #{instance_path} out`
    
    n = file[/\.(\d+)/, 1].to_i
	given_n = n - file[/\-(\d+)/, 1].to_i
	res = result.split(" ")
    printf("%-10s | %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7f|\n", file, given_n, n, res[0], res[1], res[2], res[3], given_n - res[1].to_i, elapsed)
  end
  File.delete("out")
end

desc "Run sbh general for all negative input files"
task :general_negative_no_trunc => "bin/sbh_general_no_trunc" do
  instances_dir = "instances/negative/"
  printf("%-10s | %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| \n", "File", "Words", "N", "Length", "Used w", "Made w", "Repeats", "Error", "Time")
  print "------------------------------------------------------------------------------------\n";

  Dir.foreach(instances_dir) do |file|
    instance_path = File.join(instances_dir, file);
    next unless File.file?(instance_path)

	elapsed = time {
    `bin/sbh_general_no_trunc #{instance_path} > out`
	}
	
    result = `bin/sbh_check #{instance_path} out`
    
    n = file[/\.(\d+)/, 1].to_i
	given_n = n - file[/\-(\d+)/, 1].to_i
	res = result.split(" ")
    printf("%-10s | %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7f|\n", file, given_n, n, res[0], res[1], res[2], res[3], given_n - res[1].to_i, elapsed)
  end
  File.delete("out")
end

desc "Run sbh negative for all input files"
task :negative => "bin/sbh_negative" do
  instances_dir = "instances/negative/"
  printf("%-10s | %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| %-7s| \n", "File", "Words", "N", "Length", "Used w", "Made w", "Repeats", "Error", "Time")
  print "------------------------------------------------------------------------------------\n";

  Dir.foreach(instances_dir) do |file|
    instance_path = File.join(instances_dir, file);
    next unless File.file?(instance_path)

	elapsed = time {
    `bin/sbh_negative #{instance_path} > out`
	}
	
    result = `bin/sbh_check #{instance_path} out`
    
    n = file[/\.(\d+)/, 1].to_i
	given_n = n - file[/\-(\d+)/, 1].to_i
	res = result.split(" ")
    printf("%-10s | %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7d| %-7f|\n", file, given_n, n, res[0], res[1], res[2], res[3], given_n - res[1].to_i, elapsed)
  end
  File.delete("out")
end
