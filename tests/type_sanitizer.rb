module TypeSanitizer
  def self.sanitize_c_identifier(unsanitized)
    unsanitized.gsub(/[-\/\\.,\s]/, '_')
  end
end
