using System.IO;
using UnrealBuildTool;

public class SimpleWebServerLibrary : ModuleRules {
	public SimpleWebServerLibrary(ReadOnlyTargetRules Target) : base(Target) {
		Type = ModuleType.External;

		PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "include"));

		if (Target.Platform == UnrealTargetPlatform.Win64)
		{
			// Add the import library
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "SimpleWebServer.lib"));
			// PublicDelayLoadDLLs.Add("SwappyPluginDLL.dll");
			// Ensure that the DLL is staged along with the executable
			RuntimeDependencies.Add("$(PluginDir)/Binaries/Win64/SimpleWebServer.dll");
			// RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "Win64", "SimpleWebServer.dll"));
		}
	}
}