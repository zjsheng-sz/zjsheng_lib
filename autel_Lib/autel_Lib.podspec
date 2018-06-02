#
#  Be sure to run `pod spec lint autelOBD.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
#  To learn more about Podspec attributes see http://docs.cocoapods.org/specification.html
#  To see working Podspecs in the CocoaPods repo see https://github.com/CocoaPods/Specs/
#

Pod::Spec.new do |s|

  s.name         = "autel_Lib"
  s.version      = "0.0.1"
  s.summary      = "static libes for maxiAP200"
  s.description  = <<-DESC
                    static libes for maxiAP made by Vehicle and center layer
                   DESC
  s.homepage     = "git@10.240.4.93:/git/autelOBD.git"
  s.license      = "MIT"
  s.author             = { "" => "" }

  s.source       = { :git => "git@10.240.4.93:/git/autelOBD.git" }
  # s.source_files  = "autelOBD", "autelOBD/**/*.{h,m}"
  s.exclude_files = "Classes/Exclude"

  s.vendored_frameworks = '*/*.framework'


end
