require 'rake/clean'

CLEAN.include('bin/*')
TARGETS = %w{bin/sbh_positive bin/sbh_negative bin/sbh_check bin/sbh_print_graph}
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


desc "Run sbh positive for all input files"
task :positive => "bin/sbh_positive" do
  instances_dir = "instances/positive/"
  printf("%-10s | %-6s | %-6s | %-6s | \n", "File", "N", "Result", "Error")
  print "---------------------------------------\n";

  Dir.foreach(instances_dir) do |file|
    instance_path = File.join(instances_dir, file);
    next unless File.file?(instance_path)

    `bin/sbh_positive #{instance_path} > out`
    result = `bin/sbh_check #{instance_path} out`

    n = file[/\.(\d+)[\+-]/, 1]
    printf("%-10s | %-6d | %-6d | %-6d |\n", file, n, result, n.to_i - result.to_i)
  end
  File.delete("out")
end
