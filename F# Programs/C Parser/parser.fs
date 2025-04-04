//
// Parser for SimpleC programs.  This component checks 
// the input program to see if it meets the syntax rules
// of SimpleC.  The parser returns a string denoting
// success or failure. 
//
// Returns: the string "success" if the input program is
// legal, otherwise the string "syntax_error: ..." is
// returned denoting an invalid SimpleC program.
// **--------------------	----------------------
// #     Project 4 – SimpleC Parser
// #     Course: CS 341, Spring 2024.
// #     System: Codio IDE 2024
// #     Author: Alejandro Bravo   
// #     Date: 4/3/2024
// #  ---------------------------------------------**/
// Original author:
//   Prof. Joe Hummel
//   U. of Illinois, Chicago
//   CS 341, Spring 2022
//

namespace compiler

module parser =
  //
  // NOTE: all functions in the module must be indented.
  //

  let beginswith (pattern: string) (literal: string) = //checks what the statement begins with
    literal.StartsWith(pattern)

  //
  // matchToken
  //
  let private matchToken expected_token tokens = 
    //
    // if the next token matches the expected token,  
    // keep parsing by returning the rest of the tokens.
    // Otherwise throw an exception because there's a 
    // syntax error, effectively stopping compilation
    // at the first error.
    //
    let next_token = List.head tokens
    match expected_token with
    | "identifier" | "str_literal" | "int_literal" when beginswith expected_token next_token -> //checks for literals and identifier
        List.tail tokens
    | _ ->
        if expected_token = next_token then  
            List.tail tokens
        else
            failwith ("expecting " + expected_token + ", but found " + next_token) //displays error message
  

  let isIdentifier token = //function that handles <isIdentifier> 
      true

  let isLiteralOrIdentifier token = //checks to see if literal or identifier
    beginswith "identifier" token || beginswith "str_literal" token || beginswith "int_literal" token || token = "true" || token = "false"


  let exprValue tokens =
    match tokens with
    | [] -> failwith "Empty" //empty expression
    | "true" :: rest -> ("true", rest) //handles true
    | "false" :: rest -> ("false", rest)//handles false
    | token :: rest when isLiteralOrIdentifier token -> 
        (token, rest)
    | "(" :: _ -> failwith "expecting identifier or literal, but found (" //gives error messages for mis match
    | token :: _ -> failwith ("expecting identifier or literal, but found " + token) //gives error message when no expression
 
  let parses tokens = //helper function to make sure we have an operator
      match tokens with
      | op :: rest when List.contains op ["+"; "-"; "*"; "/"; "^"; "<"; "<="; ">"; ">="; "=="; "!="] ->
          (op, rest)
      | _ -> failwith "Expected an operator" //error message when no operator

  let parseExpr tokens = // function to handle <expr-value>
      let (value1, rest1) = exprValue tokens
      match rest1 with
      | [] -> (value1, []) 
      | op :: _ when List.contains op ["+"; "-"; "*"; "/"; "^"; "<"; "<="; ">"; ">="; "=="; "!="] -> //makes sure handles expressions
          let (op, rest2) = parses rest1 
          let (value2, rest3) = exprValue rest2
          let expr = value1 + " " + op + " " + value2
          (expr, rest3)
      | _ -> (value1, rest1)

  let rec stmts tokens = //function that handles <stmts>
      match stmt tokens with
      | Some token -> morestmts token
      | None -> failwith ("expecting statement, " + "but found }") //theres nothing in the body so it finds parenthesis

  and morestmts tokens = //function that handles <morestmts>
      match tokens with
      | [] -> Some tokens 
      | _ -> //if theres more statemetns
          match stmt tokens with //checks each statement
          | Some token -> morestmts token
          | None -> Some tokens//no more statement

  and stmt tokens = //function that handles <stmt>
      match tokens with
      | ";" :: rest -> Some rest //checks if its just semi
      | "int" :: rest -> vardecl rest //checks if int/declaration
      | "cin" :: rest -> input rest //checks if input
      | "cout" :: rest -> output rest //checks if output
      | identifier :: "=" :: rest when isIdentifier identifier -> assignment tokens //checks if assignment
      | "if" :: rest -> ifstmt tokens //checks if statement
      | _::"if"::rest ->failwith ("expecting =, but found if")
      | _ -> None //Empty

  and input tokens = //function that handles <input>
    match tokens with
    | ">>" :: identifier :: ";" :: rest when beginswith "identifier" identifier ->
        Some rest
    | ">" :: _ -> failwith "expecting >>, but found >" //makes sure not only one arrow
    | ">>" :: nextToken :: _ -> failwith ("expecting identifier, but found " + nextToken) //makes sure identifier is after >>
    | nextToken :: _ -> failwith ("expecting >>, but found " + nextToken) //makes sure identifier is after >>
    | [] -> failwith "end"


  and output tokens = //function that handles <output>
    let rec outputHelper tokens value = //helper function that makes sure we do output correctly
        match tokens with
        | "<<" :: "endl" :: rest -> //can have << and endl only
            outputHelper rest (value + 1)  
        | "<<" :: token :: rest when beginswith "identifier" token || beginswith "str_literal" token || beginswith "int_literal" token || token = "true" || token = "false"  ->
            outputHelper rest (value + 1) //can have << and any identifier after  
        | ";" :: rest -> //makes sure semi colon is after
            if value > 0 then Some rest 
            else failwith "Invalid output"
        | "<<" :: nextToken :: _ -> //makes sure << isnt only thing
            failwith ("expecting identifier or literal, but found " + nextToken)
        | _ -> 
            if value > 0 then Some tokens 
            else failwith "invalid output 2"

    match tokens with //calls helper
    | "<<" :: _ -> outputHelper tokens 0

  and assignment tokens =  //function that handles <assignment>
    match tokens with
    | identifier :: "=" :: rest when beginswith "identifier" identifier -> //makes sure assignment has equal and an identifier
        let (expr, restTokens) = parseExpr rest//parses the expression
        match restTokens with
        | ";" :: rest -> Some rest//makes sure there is semicolon
    | nextToken :: _ -> failwith ("expecting identifier, but found " + nextToken)//gives error otherwise

  and ifstmt tokens = //function that handles <ifstmt>
      let t2 = matchToken "if" tokens
      let t3 = matchToken "(" t2
      let (condition, token) = parseExpr t3
      let t4 = matchToken ")" token
      let tokensAfterThen = stmt t4 |> Option.get
      else_part tokensAfterThen

  and else_part tokens = //function that handles <else_part>
      let next_token = List.head tokens
      if next_token = "else" then //makes sure theres else statement
          let t2 = matchToken "else" tokens
          stmt t2
      else
          Some tokens //can be Empty

  and vardecl tokens = //function that handles <vardecl>
    let token = matchToken "identifier" tokens
    match token with
    | ";" :: token -> Some token
    | nextToken :: _ -> failwith ("expecting ;, but found " + nextToken) //error message when semicolon isnt found

  let private simpleC tokens  = //function that handles <simpleC>
    let t2 = matchToken "void" tokens 
    let t3 = matchToken "main" t2 
    let t4 = matchToken "(" t3 
    let t5 = matchToken ")" t4 
    let t6 = matchToken "{" t5 
    let t7 = stmts t6 |> Option.get //must be list option
    let t8 = matchToken "}" t7 
    let t9 = matchToken "$" t8 
    t9;

  //
  // parse tokens
  //
  // Given a list of tokens, parses the list and determines
  // if the list represents a valid SimpleC program.  Returns
  // the string "success" if valid, otherwise returns a 
  // string of the form "syntax_error:...".
  //
  let parse tokens = 
    try
      let result = simpleC tokens
      "Success!"
    with 
      | ex -> "syntax_error: " + ex.Message