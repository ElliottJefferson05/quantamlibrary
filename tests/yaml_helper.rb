require 'yaml'

module YamlHelper
  def self.load(body)
    YAML.respond_to?(:unsafe_load) ? YAML.unsafe_load(body) : YAML.load(body)
  end

  def self.load_file(file)
    load(File.read(file))
  end
end
