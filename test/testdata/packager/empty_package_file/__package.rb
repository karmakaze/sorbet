# frozen_string_literal: true
# typed: strict
# enable-packager: true

class A < PackageSpec
  export A::AClass
  export A::BClass
end
