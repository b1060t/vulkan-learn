![](https://raw.githubusercontent.com/David-DiGioia/vulkan-diagrams/main/fence_synchronization.png)

```cpp
if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
    vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
}
imagesInFlight[imageIndex] = inFlightFences[currentFrame];
```

**`imagesInFlight[imageIndex]`是`inFlightFences[currentFrame]`的引用！！！**