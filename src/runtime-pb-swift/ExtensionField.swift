// Protocol Buffers for Swift
//
// Copyright 2014 Alexey Khohklov(AlexeyXo).
// Copyright 2008 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
import Foundation
protocol ExtensionField
{
    var fieldNumber:Int32 {get set}
    var nameOfExtension:String {get}
    var wireType:WireFormat {get}
    func initialize() -> Self
    func writeValueIncludingTagToCodedOutputStream(value:Any, output:CodedOutputStream)
    func computeSerializedSizeIncludingTag(value:Any) -> Int32
    func writeDescriptionOf(value:Any, inout output:String, indent:String)
    func mergeFromCodedInputStream(input:CodedInputStream, unknownFields:UnknownFieldSetBuilder, extensionRegistry:ExtensionRegistry, builder:ExtendableMessageBuilder, tag:Int32);
    
}