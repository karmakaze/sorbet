# typed: true

extend T::Sig

module ::Boolean
end

class TrueClass
  include Boolean
end

class FalseClass
  include Boolean
end

class BadBang
  extend T::Sig

  sig {returns(String)}
  def !()
    'bad bang override'
  end
end

sig {params(arg0: T.untyped).returns(Boolean)}
def returns_boolean(arg0)
  false
end

sig {params(x: Boolean).returns(T::Boolean)}
def boolean_to_t_boolean(x)
  x # error: Expected `T::Boolean` but found `Boolean`
end

sig {params(x: Boolean).returns(T::Boolean)}
def explicit_return(x)
  return x # error: Expected `T::Boolean` but found `Boolean`
end

sig {returns(T::Boolean)}
def can_have_spaces
  returns_boolean T.unsafe(nil) # error: Expected `T::Boolean` but found `Boolean`
end

sig {params(x: BadBang).returns(T::Boolean)}
def should_not_suggest_bang_bang(x)
  x # error: Expected `T::Boolean` but found `BadBang`
end
