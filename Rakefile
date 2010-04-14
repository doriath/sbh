desc "Build all source files"
task :build do
  cd "src"
  sh "make"
end

desc "Run sbh positive for all input files"
task :positive do
  instances_dir = "instances/positive/"
  printf("%-6s | %-6s | %-6s | \n", "N", "Result", "Error")
  print "--------------------------\n";

  Dir.foreach(instances_dir) do |file|
    next unless File.file?("#{instances_dir}#{file}")
    result = `bin/sbh_positive #{instances_dir}#{file} > out ; bin/sbh_check #{instances_dir}#{file} out`
    n = file[/\.(\d+)[\+-]/, 1]
    printf("%-6d | %-6d | %-6d |\n", n, result, n.to_i - result.to_i)
  end
  File.delete("out")
end
